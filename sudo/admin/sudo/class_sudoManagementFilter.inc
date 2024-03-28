<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)

  Copyright (C) 2024  FusionDirectory
  Copyright (C) 2024  Christian Kreidl

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


class sudoManagementFilter extends managementFilter
{

  protected function filterEntries (array $ldapEntries): array
  {
    if (!empty($this->parent->whiteList)) {
      foreach ($ldapEntries as $dn => $entry) {
        if (in_array($dn, $this->parent->whiteList['dn'])) {
          continue;
        }
        foreach ($this->parent->whiteList['branches'] as $branch) {
          if (preg_match('/'.preg_quote($branch, '/').'$/', $dn)) {
            continue 2;
          }
        }
        unset($ldapEntries[$dn]);
      }
    }
    if (isset($this->parent->blackList)) {
      foreach ($this->parent->blackList as $attr_name => $attr_values) {

        foreach ($attr_values as $match) {
          if (preg_match('/^\+/', $match)) {
            $blObjectTypes = ['nisNetgroup'];
            $match = preg_replace('/^\+/', '', $match);
          }  else {
            $blObjectTypes = ['fdTerminal', 'fdWorkstation', 'fdServer'];
          }
          foreach ($ldapEntries as $dn => $entry) {
            if (isset($entry[$attr_name])) {
              $attrs = $entry[$attr_name];
              $oclasses = $entry['objectClass'];
              if (!is_array($attrs)) {
                $attrs = [$attrs];
              }
              if (in_array($match, $attrs)) {
                foreach ($oclasses as $oclass) {
                  if (in_array($oclass, $blObjectTypes)) {
                    unset($ldapEntries[$dn]);
                  }
                }
              }
            }
          }
        }
      }
    }

    return $ldapEntries;
  }
}
