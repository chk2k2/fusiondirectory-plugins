<div class="contentboxh">
 <p class="contentboxh">
  <img src="images/launch.png" align="right" alt="[F]">{t}Filter{/t}
 </p>
</div>

<div class="contentboxb">

  {$SERVER}&nbsp;<LABEL for='SERVER'>{t}Show servers{/t}</LABEL><br>
  {$WORKSTATION}&nbsp;<LABEL for='WORKSTATION'>{t}Show workstations{/t}</LABEL><br>
  {$TERMINAL}&nbsp;<LABEL for='TERMINAL'>{t}Show terminals{/t}</LABEL><br>

 <div style="border-top:1px solid #AAAAAA"></div>
 {$SCOPE}

 <table style="width:100%;border-top:1px solid #B0B0B0;">
  <tr>
   <td>
    <label for="NAME">
     <img src="images/lists/search.png" align=middle>&nbsp;{t}Name{/t}
    </label>
   </td>
   <td>
    {$NAME}
   </td>
  </tr>
 </table>

 <table  width="100%"  style="background:#EEEEEE;border-top:1px solid #B0B0B0;">
  <tr>
   <td style="width:100%;text-align:right;">
    {$APPLY}
   </td>
  </tr>
 </table>
</div>
