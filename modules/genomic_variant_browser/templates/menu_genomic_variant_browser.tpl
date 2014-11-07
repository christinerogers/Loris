<script src="js/jquery/jquery-1.11.0.min.js" type="text/javascript"></script>
<script type="text/javascript" src="js/jquery/jquery-ui-1.10.4.custom.min.js"></script>
<script type="text/javascript" src="GetJS.php?Module=genomic_variant_browser&file=genomicMenuFilter.js"></script>
<script type="text/javascript" src="js/filterControl.js"></script>

<div class="row">
<div class="panel panel-primary">
    <div class="panel-heading" onclick="hideFilter();">
        Selection Filter
        <span class="glyphicon glyphicon-chevron-down pull-right" style="display:none" id="down"></span>
        <span class="glyphicon glyphicon-chevron-up pull-right" id="up"></span>
    </div>
    <div class="panel-body" id="panel-body">
        <form method="post" action="main.php?test_name=genomic_variant_browser">
            <div class="row">
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
                        {$form.centerID.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
                        {$form.centerID.html}
                    </div>
                </div>
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
                        {$form.SubprojectID.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
                        {$form.SubprojectID.html}
                    </div>
                </div>
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
                        {$form.DCCID.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
                        {$form.DCCID.html}
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
                        {$form.gender.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
                        {$form.gender.html}
                    </div>
                </div>
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
                        {$form.AspireDB_ID.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
                        {$form.AspireDB_ID.html}
                    </div>
                </div>
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
                        {$form.PSCID.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
                        {$form.PSCID.html}
                    </div>
                </div>
            </div> 
            <div class="row">
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
                        {$form.Variant_Type.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
                        {$form.Variant_Type.html}
                    </div>
                </div>
                <div class="form-group col-sm-8">
		</div>
	    </div> 
<!-- CNV section -->
            <div class="show-cnv-selector" style="display:none" id="show-cnv-selector">
                <div class="row">
		    <div class="col-sm-4 col-md-2 col-xs-12">
                        <input type="button" name="CNVselector" value="Show CNV Filters" id="show-cnv-selector" class="btn btn-sm btn-primary col-xs-12 show-cnv-selector" onclick="toggleCNV()" />
		    </div>
	        </div>
                <div class="row">
		   <br>
		</div>
	    </div>
            <div class="cnv-options" style="display:none" id="cnv-options">
                <div class="row">
		    <div class="col-sm-4 col-md-2 col-xs-12" >
                        <input type="button" id="hide-cnv-selector" value="Hide CNV Filters" class="btn btn-sm btn-primary col-xs-12" onclick="toggleCNV()" style="display:none;" />
		    </div>
		</div>
                <div class="row">
		   <br>
		</div>
                <div class="row">
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-5">
                            {$form.CNV_Type.label}
                        </label>
                    	<div class="col-sm-12 col-md-7">
                            {$form.CNV_Type.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-5">
        		    {$form.Common_CNV.label}
                        </label>
                    	<div class="col-sm-12 col-md-7">
        		    {$form.Common_CNV.html}
			</div>
		    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-5">
        		    {$form.Characteristics.label}
                        </label>
                    	<div class="col-sm-12 col-md-7">
        		    {$form.Characteristics.html}
			</div>
		    </div>
		</div>
                <div class="row">
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-5">
        		    {$form.Copy_Num_Change.label}
                        </label>
                    	<div class="col-sm-12 col-md-7">
        		    {$form.Copy_Num_Change.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-5">
		            {$form.Event_Name.label}
                        </label>
                    	<div class="col-sm-12 col-md-7">
        		    {$form.Event_Name.html}
			</div>
		    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-5">
        		    {$form.CNV_Description.label}
                        </label>
                    	<div class="col-sm-12 col-md-5">
        		    {$form.CNV_Description.html}
			</div>
		    </div>
		</div>
		<div class="row">
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-5">
		            {$form.Inheritance.label}
                        </label>
                    	<div class="col-sm-12 col-md-7">
        		    {$form.Inheritance.html}
			</div>
		    </div>
                    <div class="form-group col-sm-8">
		    </div>
		</div>
	    </div> <!-- end of CNV options --> 

            <div class="show-snp-selector" style="display:none" id="show-snp-selector">
                <div class="row">
		    <div class="col-sm-4 col-md-2 col-xs-12">
                        <input type="button" name="SNPselector" value="Show SNP Filters" id="show-snp-selector" class="btn btn-sm btn-primary col-xs-12 show-snp-selector" onclick="toggleSNP()" />
	            </div>
	        </div>
                <div class="row">
		   <br>
		</div>
	    </div>
    	    <div class="snp-options" style="display:none" id="snp-options">
                <div class="row">
	    	    <div class="col-sm-4 col-md-2 col-xs-12">
                        <input type="button" id="hide-snp-selector" value="Hide SNP Filters" class="btn btn-sm btn-primary col-xs-12 " onclick="toggleSNP()" style="display:none;" />
		    </div>
		</div>
                <div class="row">
		   <br>
		</div>
		<div class="row">
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.SNP_Name.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.SNP_Name.html}
			</div>
		    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.SNP_External_Source.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.SNP_External_Source.html}
			</div>
		    </div>
		</div>
		<div class="row">
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.Observed_Base.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.Observed_Base.html}
			</div>
		    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.Function_Prediction.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.Function_Prediction.html}
			</div>
		    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.SNP_Description.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.SNP_Description.html}
			</div>
		    </div>
		</div>
		<div class="row">
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.Reference_Base.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.Reference_Base.html}
			</div>
		    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.Exonic_Function.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.Exonic_Function.html}
			</div>
		    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.Damaging.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.Damaging.html}
			</div>
		    </div>
		</div>
		<div class="row">
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.Validated.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.Validated.html}
			</div>
		    </div>
                    <div class="form-group col-sm-4">
                        <label class="col-sm-12 col-md-4">
        		    {$form.Genotype_Quality.label}
                        </label>
                    	<div class="col-sm-12 col-md-8">
        		    {$form.Genotype_Quality.html}
			</div>
		    </div>
		</div>
                <div class="row">
		   <hr>
		</div>
	    </div> <!--end of SNP filters-->
    <br class="visible-xs">

	    <div class="row">
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
        		{$form.Gene_Symbol.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
        	        {$form.Gene_Symbol.html}
		    </div>
		</div>
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
      		        {$form.Chromosome.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
        	        {$form.Chromosome.html}
		    </div>
		</div>
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
        	       {$form.Platform_Name.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
        	       {$form.Platform_Name.html}
		    </div>
		</div>
	    </div>
	    <div class="row">
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
        	        {$form.Gene_Name.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
        	        {$form.Gene_Name.html}
		    </div>
		</div>
                <div class="form-group col-sm-4">
                    <label class="col-sm-12 col-md-4">
        	        {$form.Strand.label}
                    </label>
                    <div class="col-sm-12 col-md-8">
        	        {$form.Strand.html}
		    </div>
		</div>
	    </div>

            <br class="visible-xs">

	    <div class="row">
                <div class="col-sm-4 col-md-4 col-xs-12 col-md-offset-4">
                    <div class="form-group col-sm-12">
                        <label class="col-sm-12 col-md-5">
                            {$form.Show_Brief_Results.label} 
                        </label>
                        <div class="col-sm-12 col-md-7">
	    	           {$form.Show_Brief_Results.html}
		        </div>
		    </div>
	        </div>
                <div class="col-sm-4 col-md-2 col-xs-12 ">
                    <input type="submit" name="filter" value="Show Data" id="showdata" class="btn btn-sm btn-primary col-xs-12" />
                </div>
                <div class="visible-xs col-xs-12"> </div>
                <div class="visible-xs col-xs-12"> </div>
                <div class="visible-xs col-xs-12"> </div>
                <div class="visible-xs col-xs-12"> </div>
                <div class="col-sm-4 col-md-2 col-xs-12">
                   <input type="button" name="reset" value="Clear Form" class="btn btn-sm btn-primary col-xs-12" onclick="location.href='main.php?test_name=genomic_variant_browser&reset=true'" />
                </div>
                <div class="visible-xs col-xs-12"> </div>
                <div class="visible-xs col-xs-12"> </div>
                <div class="visible-xs col-xs-12"> </div>
                <div class="visible-xs col-xs-12"> </div>
            </div>
        </form>
    </div>
</div>
</div>


<!-- <table> -->
<!--  title table with pagination -->
<div class="row">
<table border="0" valign="bottom" width="100%"><tr>
    <!-- title -->
    {if $variantFilter !== "all" }
      <td class="controlpanelsection">Filtered for <strong>{$variantFilter}</strong> -- variants found: <strong>{$resultcount}</strong> total</td>
    {else}
      <td class="controlpanelsection">variants found: <strong>{$resultcount}</strong> total</td>
    {/if}
    <!-- display pagination links -->
    <td align="right">{$page_links}</td>
</tr>
</table>
<!-- </form> -->
<!-- start data table -->
<div id="carousel-example-generic" class="carousel slide" data-ride="carousel">
    <div class="carousel-inner">
        <!-- <div class="col-xs-10 col-xs-offset-1" style="overflow-y:auto"> -->
        <div class="table-scroll" id="content">
            <table  class ="table table-hover table-primary table-bordered" border="0" width="100%">
                <thead>
                    <tr class="info">
                     <th>No.</th>
                        <!-- print out column headings - quick & dirty hack -->
                        {section name=header loop=$headers}
                            <th><a href="main.php?test_name=genomic_variant_browser&filter[order][field]={$headers[header].name}&filter[order
][fieldOrder]={$headers[header].fieldOrder}">{$headers[header].displayName}</a></th>
                        {/section}
                    </tr>
                </thead>
                <tbody>
                    {section name=item loop=$items}
                        <tr>
                        <!-- print out data rows -->
                        {section name=piece loop=$items[item]}
                            {if $items[item][piece].bgcolor != ''}
                                <td style="background-color:{$items[item][piece].bgcolor}">
                            {else}
                                <td>
                            {/if}
                                {if $items[item][piece].DCCID != "" AND $items[item][piece].name == "PSCID"}
                                    {assign var="PSCID" value=$items[item][piece].value}
                                    <a href="main.php?test_name=timepoint_list&candID={$items[item][piece].DCCID}">{$items[item][piece].value}</a>

                                {elseif $items[item][piece].name == "scan_Done"}
                                {if $items[item][piece].value == 'Y'}
                                        {assign var="scan_done" value="Yes"}
                                        <a href="main.php?test_name=imaging_browser&pscid={$PSCID}&filter=Show%20Data">{$scan_done}</a>
                                {else}
                                    {assign var="scan_done" value="No"}
                                    {$scan_done}
                                {/if}
                            {else}
                                {$items[item][piece].value}
                            {/if}
                                </td>
                        {/section}
                        </tr>
                    {sectionelse}
    			<tr><td colspan="12">No variants found</td></tr>
                    {/section}
                </tbody>
            <!-- end data table -->
            </table>
        </div>
        <a class="left carousel-control"  id="scrollLeft" href="#carousel-example-generic">
            <span class="glyphicon glyphicon-chevron-left"></span>
        </a>
        <a class="right carousel-control" id="scrollRight" href="#carousel-example-generic" data-slide="next">
            <span class="glyphicon glyphicon-chevron-right"></span>
        </a>
    </div>
</div>
</div>




<!--  title table with pagination -->
<table border="0" valign="bottom" style='min-width:819px'>
<tr>
    <!-- title -->
    {if $variantFilter !== "all" }
      <td class="controlpanelsection">Filtered for <strong>{$variantFilter}</strong> -- variants found: <strong>{$resultcount}</strong> total</td>
    {else}
      <td class="controlpanelsection">variants found: <strong>{$resultcount}</strong> total</td>
    {/if}
    <!-- display pagination links -->
    <td align="right">{$page_links}</td>
</tr>
</table>

<!--
 {$headers|@print_r}
 {$type|@print_r}
--> 

<!-- start data table -->
<table class="genomictable" border="0" style='min-width:819px' cellpadding="4" cellspacing="4">
<tbody>

{section name=item loop=$items}

{cycle values="#eeeeee,#d0d0d0" assign="rowbgcolor"}
  <tr bgcolor="{$rowbgcolor}" border="0" style='min-width:819px'>
  <!-- print out data rows -->
  <td nowrap="nowrap" valign="top" border="0" cellpadding="0" style='min-width:819px'> <!-- one big cell-->
<div style='min-width:819px'>

<!-- middle table to stack sections on top of each other-->
      <table class="genomictableleft" cellpadding="2" cellspacing="0" width="100%" valign="top" nowrap="nowrap" align="left"  border="1px" bordercolor="silver" >

{if $displayFilter !== "full" } <!-- show BRIEF results --> 
        <tr align="left">
          <th nowrap="nowrap" bgcolor="darkgrey"><div style='width:30'>
            <font color="black">no</font>
          </div></th>
          <td><div style='width:35'>
            {$items[item][0].value}
          </div></td>

          <th nowrap="nowrap" bgcolor="darkgrey"><div style='width:25'>
            <font color="black">type</font>
          </div></th>
          {if $items[item][1].value == "CNV" }
            <td bgcolor="darkblue">
          {elseif $items[item][1].value == "SNP" }
            <td bgcolor="4477ff">
          {else}
            <td >
          {/if}
          <div style='width:25'>
          <font color="white"><strong> {$items[item][1].value}
          
          </strong>
          </bgcolor>
          </div></td>
          <!-- both CNV and SNP Description - field 18-->
          <th nowrap="nowrap" bgcolor="darkgrey" ><div style='width:50px;'>
            <font color="black">Gene Symbol</font>
          </div></th>
          <td ><div style='width:60px;'>{$items[item][14].value}</div></td>
          <th nowrap="nowrap" bgcolor="darkgrey"><div style='width:80px;'>
            <font color="black">Chromosome</font></div></th>
          <td><div style='width:60px;'>
            {$items[item][9].value}
          </div></td>
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Strand</font></th><td>{$items[item][10].value}</td>
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Start</font></th><td>{$items[item][11].value}</td>
</tr><tr align="left">
          <th colspan="2" nowrap="nowrap" bgcolor="darkgrey"><div style='width:65px;'>
            <font color="black">PSCID</font>
          </div></th>
          <td colspan="2"><div style='width:50px;'>{$items[item][4].value}</div></td>
          {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Copy Number&nbsp;&nbsp;</font></th><td>{$items[item][19].value}</td>
	      {elseif $items[item][1].value == "SNP" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Base (Obs:Ref)</font></th><td>{$items[item][20].value}:{$items[item][21].value}</td>
          {else} <td colspan="2" >&nbsp;</td>
          {/if}

          {if $items[item][1].value == "CNV" }
              <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Type</font></th>
              <td >{$items[item][17].value}</td>
	      {elseif $items[item][1].value == "SNP" }
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Function Prediction</font></th>
            <td>{$items[item][26].value}</td>
          {else} <td colspan="2" >&nbsp;</td>
          {/if}

          {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Characteristics&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font></th><td>{$items[item][22].value}</td>
	      {elseif $items[item][1].value == "SNP" }
             <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Exonic Function</font></th><td>{$items[item][27].value}</td>
          {else} <td colspan="2" >&nbsp;</td>
          {/if}

          {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Size</font></th><td>{$items[item][13].value}</td>
          {elseif $items[item][1].value == "SNP" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Damaging</font></th><td>{$items[item][27].value}</td>
          {else} <td colspan="2" >&nbsp;</td>
          {/if}
</tr>

{else}  <!-- ELSE show FULL RESULTS ############################ --> 
        <tr align="left">
          <th nowrap="nowrap" bgcolor="darkgrey"><div style='width:30'>
            <font color="black">no</font>
          </div></th>
          <td><div style='width:35'>
            {$items[item][0].value}
          </div></td>

          <th nowrap="nowrap" bgcolor="darkgrey"><div style='width:25'>
            <font color="black">type</font>
          </div></th>
          {if $items[item][1].value == "CNV" }
            <td bgcolor="darkblue">
          {elseif $items[item][1].value == "SNP" }
            <td bgcolor="4477ff">
          {else}
            <td >
          {/if}
          <div style='width:25'>
          <font color="white"><strong> {$items[item][1].value}
          
          </strong>
          </bgcolor>
          </div></td>
          <!-- both CNV and SNP Description - field 18-->
          <th nowrap="nowrap" bgcolor="darkgrey" ><div style='width:30px;'>
            <font color="black">Description</font></div></th>
          <td><div style='width:60px;'>
            {$items[item][18].value}
          </div></td>
          <th nowrap="nowrap" bgcolor="darkgrey" ><div style='width:50px;'>
            <font color="black">Gene Symbol</font>
          </div></th>
          <td ><div style='width:60px;'>{$items[item][14].value}</div></td>
          <th nowrap="nowrap" bgcolor="darkgrey"><div style='width:80px;'>
            <font color="black">Chromosome</font></div></th>
          <td><div style='width:60px;'>
            {$items[item][9].value}
          </div></td>
          <th nowrap="nowrap" bgcolor="darkgrey" ><div style='width:100px;'>
            <font color="black">Array Report</font>
          </div></th>
          <td><div style='width:50px;'>
	      {if $items[item][1].value == "CNV" }
            {$items[item][24].value}
	      {elseif $items[item][1].value == "SNP" }
            {$items[item][22].value}
          {else} &nbsp;
          {/if}
          </div></td>

</tr><tr align="left">
          <th colspan="2" nowrap="nowrap" bgcolor="darkgrey"><div style='width:65px;'>
            <font color="black">PSCID</font>
          </div></th>
          <td colspan="2"><div style='width:50px;'>{$items[item][4].value}</div></td>
          {if $items[item][1].value == "CNV" }
              <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Type</font></th>
              <td >{$items[item][17].value}</td>
	      {elseif $items[item][1].value == "SNP" }
              <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Name</font></th>
              <td >{$items[item][17].value}</td>
          {else} <td colspan="2" >&nbsp;</td>
          {/if}
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Gene Name</font></th><td>{$items[item][15].value}</td>
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Strand</font></th><td>{$items[item][10].value}</td>
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Platform</font></th>
          <td >{$items[item][16].value}&nbsp;</td>
</tr><tr align="left">
          <!--th colspan="2" nowrap="nowrap" bgcolor="darkgrey"><font color="black">DCCID</font></th>
          <td colspan="2">{$items[item][3].value}</td-->
          <th colspan="2" nowrap="nowrap" bgcolor="darkgrey"><font color="black">AspireDB ID</font></th>
          <td colspan="2">{$items[item][8].value}</td>

          {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Copy Number&nbsp;&nbsp;</font></th><td>{$items[item][19].value}</td>
	      {elseif $items[item][1].value == "SNP" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Observed Base</font></th><td>{$items[item][20].value}</td>
          {else} <td colspan="2">&nbsp;</td>
          {/if}

	      {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Common CNV</font></th><td>{$items[item][21].value}</td>
	      {elseif $items[item][1].value == "SNP" }
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Function Prediction</font></th>
            <td>{$items[item][26].value}</td>
          {else}<td colspan="2">&nbsp;</td>
          {/if}
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Size</font></th><td>{$items[item][13].value}</td>
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Validation Method</font></th>
	      {if $items[item][1].value == "CNV" }
            <td>{$items[item][26].value}</td>
	      {elseif $items[item][1].value == "SNP" }
            <td>{$items[item][24].value}</td>
          {else} <td>&nbsp;</td>
          {/if}
</tr>
<tr align="left">
          <th colspan="2" nowrap="nowrap" bgcolor="darkgrey"><font color="black">Subproject</font></th>
          <td colspan="2">{$items[item][6].value}</td>

	      {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Event Name</font></th><td>{$items[item][20].value}</td>
	      {elseif $items[item][1].value == "SNP" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Reference Base</font></th><td>{$items[item][21].value}</td>
          {else}<td colspan="2">&nbsp;</td>
          {/if}
          {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Characteristics&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font></th><td>{$items[item][22].value}</td>
	      {elseif $items[item][1].value == "SNP" }
             <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Exonic Function</font></th><td>{$items[item][27].value}</td>
          {else} <td colspan="2">&nbsp;</td>
          {/if}
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Start</font></th><td>{$items[item][11].value}</td>
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Validated</font></th>
          <td>{$items[item][25].value}</td>
</tr><tr align="left">
          <th colspan="2" nowrap="nowrap" bgcolor="darkgrey"><font color="black">Gender</font></th>
          <td colspan="2">{$items[item][5].value}</td>

	      {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">&nbsp;</font></th>
            <td>&nbsp; </td>
          {elseif $items[item][1].value == "SNP" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Damaging</font></th><td>{$items[item][27].value}</td>
          {else} <td colspan="2">&nbsp;</td>
          {/if}

	      {if $items[item][1].value == "CNV" }
            <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Inheritance</font></th>
            <td>{$items[item][23].value}</td>
          {elseif $items[item][1].value == "SNP" }
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Genotype Quality</font></th>
            <td>{$items[item][28].value}</td>
          {else} <td colspan="2">&nbsp;</td>
          {/if}
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">End</font></th><td>{$items[item][12].value}</td>
          <th nowrap="nowrap" bgcolor="darkgrey"><font color="black">Markers</font></th>
	      {if $items[item][1].value == "CNV" }
            <td ">{$items[item][25].value}</td>
	      {elseif $items[item][1].value == "SNP" }
            <td >{$items[item][21].value}</td>
          {else} <td colspan="2">&nbsp;</td>
          {/if}
</tr>

{/if}  <!-- end of ELSE show FULL RESULTS --> 

        </table>
     </div>
     </td>
   </tr>
{sectionelse}
    <tr><td colspan="3">No variants found</td></tr>
{/section}
                
<!-- end data table -->
</tbody>
</table>

