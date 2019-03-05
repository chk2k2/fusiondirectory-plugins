<div id="{$sectionId}" class="plugin-section{$sectionClasses}">
  <span class="legend">
    {$section}
  </span>
  <div>
    {if $attributes.dump}
      {function name=printNodes}
        <ul>
          {foreach from=$nodes key=key item=node}
            <li>
              <a href="#" onclick="Effect.toggle('toggle_{$key}', 'blind', {literal}{ duration: 0.3 }{/literal}); return false;">
                {$node.name}
              </a>
              <div id="toggle_{$key}" style="overflow: visible; display: none;">
                <table class="listingTable">
                  <tbody>
                    {foreach from=$node.attrs key=label item=values}
                      {foreach from=$values item=value}
                        <tr>
                          <th>{$label}</th>
                          <td>{$value}</td>
                        </tr>
                      {/foreach}
                    {/foreach}
                  </tbody>
                </table>
              </div>
              {call name=printNodes nodes=$node.subnodes}
            </li>
          {/foreach}
        </ul>
      {/function}
      {call name=printNodes nodes=$attributes.dump}
    {else}
      <img alt="{t}Insufficient rights{/t}" src="geticon.php?context=status&icon=dialog-error&size=16" class="center"/>&nbsp;
      <b>You have insufficient rights for using this tab</b>
    {/if}
  </div>
</div>

