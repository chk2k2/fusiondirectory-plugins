<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)
  Copyright (C) 2003-2010  Cajus Pollmeier
  Copyright (C) 2011-2019  FusionDirectory

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/

/* Basic setup, remove eventually registered sessions */
require_once("../include/php_setup.inc");
require_once("functions.inc");
require_once("variables.inc");

/* Set headers */
header('Content-type: text/html; charset=UTF-8');
header('X-XSS-Protection: 1; mode=block');
header('X-Content-Type-Options: nosniff');
header('X-Frame-Options: deny');

/* Set the text domain as 'fusiondirectory' */
$domain = 'fusiondirectory';
bindtextdomain($domain, LOCALE_DIR);
textdomain($domain);

/* Remember everything we did after the last click */
session::start();
reset_errors();

CSRFProtection::check();

$ui     = session::get('ui');
$config = session::get('config');

/* If SSL is forced, just forward to the SSL enabled site */
if (($config->get_cfg_value('forcessl') == 'TRUE') && ($ssl != '')) {
  header("Location: $ssl");
  exit;
}

timezone::setDefaultTimezoneFromConfig();

/* Check for invalid sessions */
if (session::get('_LAST_PAGE_REQUEST') != '') {
  /* check FusionDirectory.conf for defined session lifetime */
  $max_life = $config->get_cfg_value('sessionLifetime', 60 * 60 * 2);

  if ($max_life > 0) {
    /* get time difference between last page reload */
    $request_time = (time() - session::get('_LAST_PAGE_REQUEST'));

    /* If page wasn't reloaded for more than max_life seconds
     * kill session
     */
    if ($request_time > $max_life) {
      session::destroy('main.php called with expired session');
      header('Location: index.php?signout=1&message=expired');
      exit;
    }
  }
}
session::set('_LAST_PAGE_REQUEST', time());

session::set('DEBUGLEVEL', $config->get_cfg_value('DEBUGLEVEL'));

/* Set template compile directory */
$smarty->compile_dir = $config->get_cfg_value('templateCompileDirectory', SPOOL_DIR);

Language::init();

LoginWebAuthnPost::processWebAuthnJavascriptRequests();
LoginWebAuthnPost::displaySecondFactorPage();
