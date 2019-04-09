<body onLoad="javascript:$$('div.debug_div').each(function (a) { a.hide(); });">
  {* FusionDirectory user reminder - smarty template *}
  {$php_errors}
  {$msg_dialogs}

  <div id="window-container">

    <div id="window-div">

        <div id="window-titlebar">
          <p>
            <img class="center" src="geticon.php?context=types&amp;icon=user&amp;size=48" alt="{t}User{/t}" title="{t}User{/t}"/>
            {t}Expiration postpone{/t}
          </p>
        </div>
        <div id="window-content">
          <!-- Display error message on demand -->
          <span class="warning"> {$message} </span>
          {if $success}
            <div class="success">
              <img class="center" src="geticon.php?context=status&amp;icon=task-complete&amp;size=16" alt="{t}Success{/t}" title="{t}Success{/t}">&nbsp;
              <b>{t}Your expiration has been postponed successfully.{/t}</b>
              <br/>
              <br/>
              <a href="./">Return to login screen</a>
            </div>
          {else}
            <div class="error">
              <img class="center" src="geticon.php?context=status&amp;icon=task-failure&amp;size=16" alt="{t}Error{/t}" title="{t}Error{/t}">&nbsp;
              <b>{t}There was a problem{/t}</b>
            </div>
          {/if}
        </div>
    </div>
  </div>
  {include file={filePath file="copynotice.tpl"}}
  <script type="text/javascript">
    <!-- // Error Popup
    next_msg_dialog();
    -->
  </script>
</body>
</html>
