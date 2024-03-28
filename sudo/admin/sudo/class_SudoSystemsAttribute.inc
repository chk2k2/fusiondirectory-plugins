<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)

  Copyright (C) 2003  Cajus Pollmeier
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

class sudoSystemSelect extends systemSelect
{
  protected function setUpFilter (array $filterElementDefinitions)
  {
    $this->filter   = new sudoManagementFilter($this, NULL, $filterElementDefinitions);
  }
}

class SudoSystemSelectDialog extends SystemSelectDialog
{
  protected $dialogClass = 'sudoSystemSelect';
}

class SudoSystemsAttribute extends SystemsAttribute
{
  protected $dialogClass  = 'SudoSystemSelectDialog';

  function __construct (string $label, string $description, string $ldapName, bool $required, array $objectTypes = ['terminal', 'workstation', 'server'], array $defaultValue = [], string $store_attr = 'cn', string $display_attr = 'cn', array $filterElementDefinitions = NULL, string $acl = '')
  {
    if (class_available('netgroup')) {
      array_push($objectTypes, 'netgroup');
    }

    parent::__construct($label, $description, $ldapName, $required, $objectTypes, $defaultValue, $store_attr, $display_attr, $filterElementDefinitions, $acl);
  }

  function renderButtons ()
  {
    $id = $this->getHtmlId();
    $buttons  = $this->renderInputField(
      'submit', 'add'.$id.'_ALL',
      [
        'value'           => 'ALL',
        'formnovalidate'  => 'formnovalidate'
      ]
    );
    return $buttons.parent::renderButtons();
  }

  public function htmlIds (): array
  {
    $id = $this->getHtmlId();
    $ids = parent::htmlIds();
    $ids[] = 'add'.$id.'_ALL';
    return $ids;
  }

  function loadPostValue ()
  {
    parent::loadPostValue();
    if ($this->isVisible()) {
      if (isset($_POST['add'.$this->getHtmlId().'_ALL'])) {
        $this->value    = ['ALL'];
        $this->displays = ['ALL'];
        $this->types    = [FALSE];
      }
    }
  }

  function addValue (string $dn, $attrs = NULL)
  {
    if (isset($this->value[0]) && ($this->value[0] === 'ALL')) {
      $this->removeValue(0);
    }

    if (
        ($this->isTemplate() && ($attrs === NULL)) ||
        ($this->store_attr == 'dn')
      ) {
      $value = $dn;
    } elseif (in_array('nisNetgroup', $attrs['objectClass'])) {
      $value = "+".trim($attrs['cn'][0]);
    } else {
      $value = $attrs[$this->store_attr][0];
    }
    if (!in_array($value, $this->value) && !in_array('!'.$value, $this->value)) {
      end($this->value);
      $new_key = key($this->value) + 1;
      $this->value[$new_key] = $value;
      $this->fillDisplayValueFrom($new_key, $attrs);
    }
  }

  protected function fillDisplayValue ($i)
  {
    if ($this->value[$i] === 'ALL') {
      $this->displays[$i] = 'ALL';
      $this->types[$i]    = FALSE;
    } else {
      $value = $this->value[$i];
      if (preg_match('/^\+/', $value)) {
        try {
          $objects = objects::ls(['netgroup'], $this->selectManagementParameters[2], NULL, '(cn='.ldap_escape_f(preg_replace('/^\+/', '', $value)).')');
        } catch (EmptyFilterException $e) {
          $objects = [];
        }
      } else {
        $objects = objects::ls(['terminal', 'workstation', 'server'], $this->selectManagementParameters[2], NULL, '(cn='.ldap_escape_f($value).')');
      }

      if (empty($objects) && $this->isTemplate()) {
        $this->fillDisplayValueFrom($i, NULL);
      } else {
        $this->fillDisplayValueFrom($i, reset($objects));
      }
    }
  }
}
