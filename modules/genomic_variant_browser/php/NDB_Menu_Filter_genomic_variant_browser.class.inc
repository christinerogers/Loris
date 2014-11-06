<?php
require_once 'NDB_Menu_Filter.class.inc';

/**
 * Breakdown of returned variants, filterable by candidate, CNV or SNP : 
 * GENOMIC VARIANT viewer - 13.11.15 
 * @package main
 */
class NDB_Menu_Filter_genomic_variant_browser extends NDB_Menu_Filter
{

    /**  Array to hold multiple queries to insert into tpl_data
     *    See overloaded _getList() function below from Menu_Filter class 
     */
    var $_basicColumns; // cols valid across all variant types 
    var $_queryArray; 
    var $_CNVcols; 
    var $_SNPcols; 

    /**
     * overloading this method to allow access to site users (their own site only) and users w/ multisite privs
     * @note   overloaded function
     * @return bool
     * @access private
     */
    function _hasAccess()
    {
        // create user object
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        // allow only to view own site data
        $site =& Site::singleton($user->getData('CenterID'));
        if (PEAR::isError($site)) {
            return PEAR::raiseError("DB Error: ".$site->getMessage());
        }

        return ($user->hasPermission('access_all_profiles') ||  $site->isStudySite());
    }

    function _setupVariables()
    {
        // set the class variables
        // $this->columns 
        $this->_basicColumns = array('psc.Name AS PSC', 'candidate.CandID AS DCCID', 
                'candidate.PSCID', 'candidate.Gender', 
                'cohort.SubprojectID as Subproject',
                'DATE_FORMAT(candidate.DoB,\'%Y-%m-%d\') AS DoB', 
                'candidate.ExternalID as aspireDBID', 
                'genome_loc.Chromosome as Chromosome', 
                'genome_loc.Strand as Strand', 
                'genome_loc.StartLoc as StartLoc', 
                'genome_loc.EndLoc as EndLoc', 
                'genome_loc.Size as Size', 
                'gene.OfficialSymbol as Gene_Symbol', 
                'gene.OfficialName as Gene_Name', 
                'platform.Name as Platform_Name');

        // basic + CNV + (SNP less commonColumns that CNV also has)
        // Array_Report has CNV and SNP versions. 
        $this->columns = array('psc.Name AS PSC', 'candidate.CandID AS DCCID', 
                'candidate.PSCID', 'candidate.Gender', 
                'cohort.SubprojectID as Subproject',
                'DATE_FORMAT(candidate.DoB,\'%Y-%m-%d\') AS DoB', 
                'candidate.ExternalID as aspireDBID', 
                'genome_loc.Chromosome as Chromosome', 
                'genome_loc.Strand as Strand', 
                'genome_loc.StartLoc as StartLoc', 
                'genome_loc.EndLoc as EndLoc', 
                'genome_loc.Size as Size', 
                'gene.OfficialSymbol as Gene_Symbol', 
                'gene.OfficialName as Gene_Name', 
                'platform.Name as Platform_Name' ,
                'variant_type as Variant_Type', 
                'CNV.Type as CNV_Type', 
                'CNV.Description as CNV_Description', 
                'CNV.CopyNumChange as Copy_Num_Change',
                'CNV.EventName as Event_Name',
                'CNV.Common_CNV as Common_CNV',
                'CNV.Characteristics as Characteristics',
                'CNV.Inheritance as Inheritance', 
                'CNV.ArrayReport as Array_Report',
                'CNV.Markers as Markers',
                'CNV.ValidationMethod as Validation_Method', 
                'SNP.SNPExternalName as SNP_Name', 
                'SNP.Description as SNP_Description', 
                'SNP.SNPExternalSource as External_Source',
                'SNP.ObservedBase as Observed_Base',
                'SNP.ReferenceBase as Reference_Base',
                //      'SNP.ArrayReport as Array_Report',
                //      'SNP.Markers as Markers',
                //      'SNP.ValidationMethod as Validation_Method',
                'SNP.Validated as Validated',
                'SNP.FunctionPrediction as Function_Prediction',
                'SNP.Damaging as Damaging', 
                'SNP.GenotypeQuality as Genotype_Quality',
                'SNP.ExonicFunction as Exonic_Function'); 

        $config=&NDB_Config::singleton();

        $queryArray=array( 
                "CNV"=>array( "columns"=>array(), "query" => "NULL"), 
                "SNP"=>array( "columns"=>array(), "query" => "NULL")  ); 

        //  CNV        
        $this->_CNVcols = array( '\'CNV\' as variant_type',
                'CNV.Type as CNV_Type', 'CNV.Description as CNV_Description', 
                'CNV.CopyNumChange as Copy_Num_Change',
                'CNV.EventName as Event_Name',
                'CNV.Common_CNV as Common_CNV',
                'CNV.Characteristics as Characteristics',
                'CNV.Inheritance as Inheritance', 
                'CNV.ArrayReport as Array_Report',
                'CNV.Markers as Markers',
                'CNV.ValidationMethod as Validation_Method'); 
        $queryArray['CNV']['columns']=array_merge($this->_basicColumns, $this->_CNVcols ); 

        // CNV query
        // $queryArray['CNV']['query'] = " FROM psc, candidate , session, CNV
        $queryArray['CNV']['query'] = " FROM candidate 
            LEFT JOIN (select s.CandID, min(s.subprojectID) as SubprojectID
                from session s GROUP BY s.CandID) AS cohort
                ON cohort.CandID=candidate.CandID  
            LEFT JOIN psc on psc.CenterID=candidate.CenterID
            JOIN CNV on candidate.CandID = CNV.CandID
            LEFT JOIN genome_loc on genome_loc.GenomeLocID=CNV.GenomeLocID  
            LEFT JOIN gene on gene.GenomeLocID = CNV.GenomeLocID 
            LEFT JOIN platform on CNV.PlatformID = platform.PlatformID
            WHERE 
            candidate.PSCID like 'DCC2%' AND 
            candidate.Entity_type = 'Human' AND candidate.Active = 'Y' "; 

        // common columns are ArrayReport, Markers, ValidationMethod -- ? 

        // SNP         
        $this->_SNPcols = array( '\'SNP\' as variant_type',
                'SNP.SNPExternalName as SNP_Name', 
                'SNP.Description as SNP_Description', 
                'SNP.SNPExternalSource as External_Source',
                'SNP.ObservedBase as Observed_Base',
                'SNP.ReferenceBase as Reference_Base',
                'SNP.ArrayReport as Array_Report',
                'SNP.Markers as Markers',
                'SNP.ValidationMethod as Validation_Method',
                'SNP.Validated as Validated',
                'SNP.FunctionPrediction as Function_Prediction',
                'SNP.Damaging as Damaging', 
                'SNP.GenotypeQuality as Genotype_Quality',
                'SNP.ExonicFunction as Exonic_Function'); 
        $queryArray['SNP']['columns']=array_merge($this->_basicColumns, $this->_SNPcols );  

        // SNP query  
        $queryArray['SNP']['query'] = " FROM candidate
            LEFT JOIN (select s.CandID, min(s.subprojectID) as SubprojectID 
                from session s GROUP BY s.CandID) AS cohort
                ON cohort.CandID=candidate.CandID  
            LEFT JOIN psc on psc.CenterID=candidate.CenterID
            JOIN SNP on candidate.CandID = SNP.CandID
            LEFT JOIN genome_loc on genome_loc.GenomeLocID=SNP.GenomeLocID  
            LEFT JOIN gene on gene.GenomeLocID = SNP.GenomeLocID 
            LEFT JOIN platform on SNP.PlatformID = platform.PlatformID
            WHERE 
            candidate.PSCID like 'DCC2%' AND 
            candidate.Entity_type = 'Human' AND candidate.Active = 'Y' ";

        /* // previous version: 
        $queryArray['SNP']['query'] = " FROM psc, candidate , session, SNP 
            LEFT JOIN genome_loc on genome_loc.GenomeLocID=SNP.GenomeLocID  
            LEFT JOIN gene on gene.GenomeLocID = SNP.GenomeLocID 
            LEFT JOIN platform on SNP.PlatformID = platform.PlatformID
            WHERE 
            candidate.CandID=SNP.CandID  AND 
            candidate.CenterID = psc.CenterID AND 
            candidate.CandID=session.CandID  AND 
            candidate.Entity_type = 'Human' AND candidate.Active = 'Y' ";
        */

        $user =& User::singleton();
        if (!$user->hasPermission('access_all_profiles')) {
            $this->query .= " AND candidate.CenterID=" . $user->getCenterID();

            foreach ($queryArray as $variantType => $fields ) {  // note & reference
                $fields['query'] .= " AND candidate.CenterID=" . $user->getCenterID();
            } 
        }

        $this->order_by = 'psc.Name, candidate.CandID DESC';
        $this->validFilters = array('candidate.CenterID', 
                'candidate.CandID',
                'candidate.PSCID', 
                'candidate.Gender', 
                'cohort.SubprojectID',
                'candidate.DoB', 
                'candidate.ExternalID', 
                'variant_type', 
                'show_brief_results', 
                'CNV.Type', 'CNV.CopyNumChange', 
                'CNV.Description',
                'CNV.EventName',
                'CNV.Common_CNV',
                'CNV.Characteristics',
                'CNV.Inheritance',
                'SNP.SNPExternalName', 'SNP.Description', 'SNP.SNPExternalSource', 
                'SNP.ObservedBase',
                'SNP.ReferenceBase',
                'SNP.Validated',
                'SNP.FunctionPrediction',
                'SNP.Damaging',
                'SNP.GenotypeQuality',
                'SNP.ExonicFunction',
//                'CNV.ArrayReport',
//                'CNV.Markers',
//                'CNV.ValidationMethod',
//'SNP.ArrayReport',
//'SNP.Markers',
//'SNP.ValidationMethod',
                'genome_loc.Chromosome', 'genome_loc.Strand', 
                'gene.OfficialSymbol',  'gene.OfficialName', 
                'platform.Name' );

        $this->formToFilter = array(
                'centerID' => 'candidate.CenterID',
                'DCCID' => 'candidate.CandID',
                'PSCID' => 'candidate.PSCID',
                'gender' => 'candidate.Gender',
                'SubprojectID' => 'cohort.SubprojectID',
                'AspireDB_ID' => 'candidate.ExternalID', 
                'Variant_Type' => 'variant_type',
                'Show_Brief_Results' => 'show_brief_results',
                'CNV_Type' => 'CNV.Type',
                'Copy_Num_Change' => 'CNV.CopyNumChange',
                'CNV_Description' => 'CNV.Description', 
                'Event_Name' => 'CNV.EventName',
                'Common_CNV' => 'CNV.Common_CNV',
                'Characteristics' => 'CNV.Characteristics',
                'Inheritance' => 'CNV.Inheritance', 
                'SNP_Name' => 'SNP.SNPExternalName',
                'SNP_Description' => 'SNP.Description',
                'SNP_External_Source' => 'SNP.SNPExternalSource',
                'Observed_Base' => 'SNP.ObservedBase',
                'Reference_Base' => 'SNP.ReferenceBase',
                'Validated' => 'SNP.Validated',
                'Function_Prediction' => 'SNP.FunctionPrediction',
                'Damaging' => 'SNP.Damaging', 
                'Genotype_Quality' => 'SNP.GenotypeQuality',
                'Exonic_Function' => 'SNP.ExonicFunction',
//                'Array_Report' => 'CNV.ArrayReport',
//                'Markers' => 'CNV.Markers',
//                'Validation_Method' => 'CNV.ValidationMethod', 
//'Array_Report' => 'SNP.ArrayReport',
//'SNP.Markers as Markers',
//'SNP.ValidationMethod as Validation_Method',
                'Chromosome' => 'genome_loc.Chromosome',
                'Strand' => 'genome_loc.Strand',
                'Gene_Symbol' => 'gene.OfficialSymbol',
                'Gene_Name' => 'gene.OfficialName',
                'Platform_Name' => 'platform.Name'   ); 

        $this->_queryArray = $queryArray; 
        return true;
    }

    function _setFilterForm()
    {
        // create user object
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        // PSC
        if ($user->hasPermission('access_all_profiles')) {
            // get the list of study sites - to be replaced by the Site object
            $list_of_sites =& Utility::getSiteList();
            if(PEAR::isError($list_of_sites)) {
                return PEAR::raiseError("DB Error: ".$list_of_sites->getMessage());
            }
            if(is_array($list_of_sites)) $list_of_sites = array('' => 'Any') + $list_of_sites;
        }
        else {
            // allow only to view own site data
            $site =& Site::singleton($user->getData('CenterID'));
            if (PEAR::isError($site)) {
                return PEAR::raiseError("DB Error: ".$site->getMessage());
            }
            if ($site->isStudySite()) {
                $list_of_sites = array($user->getData('CenterID') => $user->getData('Site'));
            }
        }

        // SubprojectID
        $list_of_subprojects =& Utility::getSubprojectList();

        // add form elements
        $this->addSelect('centerID', 'Site:', $list_of_sites);
        $this->addBasicText('DCCID', 'DCCID:');
        $this->addBasicText('PSCID', 'PSCID:');
        $this->addBasicText('AspireDB_ID', 'AspireDB ID:');
        $this->addSelect('gender', 'Gender:', array('' => 'All', 'Male' => 'Male', 'Female' => 'Female'));
        $this->addSelect('SubprojectID', 'Subproject:', array('' => 'Any') + $list_of_subprojects);
        $this->addBasicText('dob', 'Date of Birth:', array('maxlength' => 10));

        $variant_type_options = array(null => 'All', 'CNV' => 'CNV only', 'SNP' => 'SNP only');
        $this->addSelect('Variant_Type','Variant Type:', $variant_type_options);

        $show_results_options = array('brief' => 'Brief results', 'full' => 'Full results');
        $this->addSelect('Show_Brief_Results','Display:', $show_results_options);

        // CNV 
        $CNV_Type_options = array(null => 'All', 'gain' => 'gain', 'loss' => 'loss', 'unknown' => 'Unknown');
        $this->addSelect('CNV_Type','CNV Type:', $CNV_Type_options);
        $this->addBasicText('Copy_Num_Change','Copy Number Change:');
        $this->addBasicText('CNV_Description','CNV Description:');
        $this->addBasicText('Event_Name','Event Name:');

        $Common_CNV_options = array(null => 'Any', 'Y' => 'Yes', 'N' => 'No');
        $this->addSelect('Common_CNV','Common CNV:', $Common_CNV_options);
        $Characteristics_options= array(null => 'Any', 'Benign' => 'Benign', 'Pathogenic' => 'Pathogenic', 'Unknown'=>'Unknown');
        $this->addSelect('Characteristics','Characteristics:', $Characteristics_options);
        $Inheritance_options= array(null => 'Any', 'de novo' => 'de novo', 'maternal' => 'maternal', 'paternal'=>'paternal', 'unclassified'=>'unclassified', 'unknown'=>'unknown', 'NA'=>'NA');
        $this->addSelect('Inheritance','Inheritance:', $Inheritance_options);

        // SNP 
        $this->addBasicText('SNP_Name','SNP Name:');
        $this->addBasicText('SNP_Description','SNP Description:');
        $this->addBasicText('SNP_External_Source', 'SNP External Source:');
        $Base_options= array(null => 'Any', 'A' => 'A', 'C' => 'C', 'T'=>'T', 'G'=>'G');
        $this->addSelect('Observed_Base','Observed Base:', $Base_options);
        $this->addSelect('Reference_Base','Reference Base:', $Base_options);

        $this->addSelect('Validated','Validated:', array(null=>'Any', '0'=>'0', '1'=>'1'));
        $this->addSelect('Function_Prediction','Function Prediction:', array(null=>'Any', 'exonic'=>'exonic', 'ncRNAexonic'=>'ncRNAexonic', 'splicing'=>'splicing', 'UTR3'=>'UTR3', 'UTR5'=>'UTR5'));
        $this->addSelect('Damaging','Damaging:', array(null=>'Any', 'D'=>'D', 'NA'=>'NA'));
        $this->addBasicText('Genotype_Quality','Genotype Quality:');
        $this->addBasicText('Exonic_Function','Exonic Function:');

        $this->addBasicText('Chromosome','Chromosome:');
        $this->addBasicText('Strand','Strand:');
        $this->addBasicText('Gene_Symbol','Gene Symbol:');
        $this->addBasicText('Gene_Name','Gene Name:');
        $this->addBasicText('Platform_Name','Platform Name:');

	// common to both, for now... not sure these are relevant to CNV at all. 
        $Array_Report_options= array(null => 'Any', 'Abnormal' => 'Abnormal', 'Normal' => 'Normal', 'Pending'=>'Pending', 'Uncertain'=>'Uncertain');
        $this->addSelect('Array_Report','Array Report:', $Array_Report_options);
        $this->addSelect('Markers','Markers:');
        $this->addSelect('Validation_Method','Validation Method:');

        return true;
    }


    function _setDataTableRows($count)
    {
        // create user object
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }
        $subprojectlist=Utility::getSubprojectList();
        $debug = false; // for printing 
        if ($debug) { 
            $sz= sizeof($this->list); 
            print "<br><br>Size of list: $sz ;; ###<br>"; 
            print_r($this->list); 
        }

        $x = 0; // row counter 
        foreach ($this->list as $item) { // for each record returned
            //assign row number for display purposes, at array element 0
            $this->tpl_data['items'][$x][0]['value'] = $x + $count;

            // print variant type first  
            $this->tpl_data['items'][$x][1]['value'] = $item['variant_type'];

            //print out data columns, starting at array element 2
            $i = 2;
            foreach ($item as $key => $val) {

                //if it's a non-PSC user show the URL to the timepoint list on PSCID field
                if ($key == 'PSCID' && $user->hasPermission('access_all_profiles')) {
                    $this->tpl_data['items'][$x][$i]['DCCID'] = $item['DCCID'];
                }
                elseif ($key == 'variant_type' ) { // ignore 
                    continue; 
                }

                // Default assignment:  whatever is in the results goes in. 
                // column counter $i does not matter for retrieval/display
                $this->tpl_data['items'][$x][$i]['name'] = $key;
                $this->tpl_data['items'][$x][$i]['value'] = $val;

                if ($key=='Subproject'){
                    $this->tpl_data['items'][$x][$i]['value'] = $subprojectlist[$val];
                }

                // Since data table is not displayed in a grid with column headers,
                // data fields do not need to be aligned with tpl_data headers
                // Whatever is returned by the query is loaded in tpl_data --
                // no need to null CNV fields for a SNP query, and vice versa. 

                $debug=false; // true; 
                if ($debug && $key == 'PSCID' ){ // && ($val == "DCC0031" || $val == "DCC0001"))
                    print "<br> ";
                }  
                elseif ($key == 'PSC') {
                    $debug=false; // true; 
                } 
                if ($debug) { 
                    $n=$this->tpl_data['items'][$x][$i]['name'];
                    $v=$this->tpl_data['items'][$x][$i]['value'];
                    print "<br> field $i NAME: $n VAL: $v "; 
                } 

                $i++;
            } // end per item (column) 

            $x++;

        } // foreach row x 

        $debug=false; 
        if ($debug) {
            $len = count( $this->tpl_data ); 
            print "PRINTING: <br> TPL DATA $len items: "; 
            //         print_r($this->tpl_data); 
            print "<br><br> PRINT tpl_data headers : <br>"; 
            print_r( $this->tpl_data["headers"]); 
            print "<br><br> PRINT tpl_data items: <br>"; 
            print_r( $this->tpl_data["items"]); 
            print "<br><br> "; 
        }


        return true;
    }

    /**  OVERRIDING function from NDB_Menu_Filter class 
     * in order to run 2 separate queries and combine into tpl_data
     * for CNV and SNP variants (2 separate types, separate tables)
     * 
     * Returns a list of candidates, users, etc.
     *
     * @return array
     * @throws PEAR_Error
     * @access private
     */

    function _getList()
    {
        // create DB object
        $DB =& Database::singleton();
        if(PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }

        $variantFilter = "all"; // default, if variant type filter is empty
        if (is_array($this->filter) && array_key_exists("variant_type", $this->filter)
            && !empty($this->filter['variant_type']) ) {
            $variantFilter = $this->filter['variant_type'];  // CNV or SNP 
        }
        $displayFilter = "brief"; 
        if (is_array($this->filter) && array_key_exists("show_brief_results", $this->filter)
            && !empty($this->filter['show_brief_results']) ) {
            // $debug=true;
            if ($debug) { print "<br>### Filter: ".$this->filter['show_brief_results']." <br>"; } 
            $displayFilter = $this->filter['show_brief_results'];  // Brief or Full 
        }

        $_results = array(); // initialized null 
        foreach ( $this->_queryArray as $vartype =>$_thisQuery ) {  

            // $debug=true; 
            if ($debug) { 
                print "<br><br> processing query vartype $vartype <br>"; 
                if (is_array( $_thisQuery)) { 
                    print_r($_thisQuery) ; 
                }
                print "<br>### Filters:<br>"; 
                print_r($this->filter) ; 
                print "<br><br>"; 
            }

            // "Filter" here for variant type: abort query if non-selected variant type
            // e.g. if "Variant Type" filter is set to "CNV", 
            // then do not execute "SNP" vartype query
            if ($variantFilter != "all" && $variantFilter != $vartype ) { 
                if ($debug) 
                    print "<br>Skipping $vartype query : variantFilter = $variantFilter <br>"; 

                continue; // Next query
            }
            if ($debug) print "<br>Else processing $vartype query : filter = $variantFilter <br>"; 

            // make the SELECT statement
            $query = "SELECT ";
            if (is_array($_thisQuery['columns']) && count($_thisQuery['columns']) > 0) {
                $query .= implode(', ', $_thisQuery['columns']);
            } else {
                $query .= "*";
            }

            // $debug=true; 
            if ($debug) {
                print "<br> COLUMNS to select: <br>"; 
                foreach ( $_thisQuery['columns'] as $id => $col) {
                    print "$id : $col<br>";    
                }
            }
            // add the base query
            // $query .= $this->query;
            $query .= $_thisQuery['query']; ###

            // add filters to query
            if (is_array($this->filter) && count($this->filter) > 0) {
                foreach ($this->filter as $key => $val) {
                    if ((!empty($val) || $val === '0') 
                        && $key != 'order' 
                        && $key != 'variant_type' && $key != 'show_brief_results') {

                        if ($debug) print "<br>adding Filter to query: $key : $val "; 

                        // special rule for dropdowns where value is numeric
                        if (strtolower(substr($key, -8)) == 'centerid' ||
                                strtolower(substr($key, -10)) == 'categoryid' ||
                                strtolower(substr($key, -6)) == 'gender' ||
                                strtolower(substr($key, -10)) == 'aspireDBID' ||
                                strtolower(substr($key, -6)) == 'strand' ) {
                            // strict matching: = instead of Like '% %' 
                            $query .= " AND $key = '$val' ";
                        }
                        elseif ( substr($key, 0, 4) == 'CNV.') { // CNV.Type 
                            if ( $vartype == "CNV" ) {  // strict matching 
                                $query .= " AND $key = '$val' ";
                            } // else ignore
                        } 
                        elseif ( substr($key, 0, 4) == 'SNP.') { // SNP table filter 
                            if ( $vartype == "SNP" ) { // strict matching
                                $query .= " AND $key = '$val' ";
                            } // else ignore
                        }
                        elseif (strtolower(substr($key, -10)) == 'chromosome' ) {
                            // comma delimited matching: add OR clauses 
                            $terms = explode( ',', $val); 
                            if ( sizeof($terms) == 1 ) {
                                $query .= " AND $key = '$val' ";
                            }
                            else { // multiple search terms 
                                $sub = " AND ( ";
                                foreach ( $terms as $oneTerm ) {
                                    $a = trim($oneTerm) ; 
                                    $sub .= "$key = '$a' OR ";
                                }
                                $query .= preg_replace('/ OR $/', ' )', $sub); 
                            }
                        }
                        else {                            
                            $query .= " AND $key LIKE '%$val%' ";
                        }
                    }
                }
            }

            // add GROUP BY if applicable
            if (!empty($this->group_by)) {
                $query .= " GROUP BY $this->group_by ";
            }
            // add HAVING clause (for restricting aggregates)
            if(!empty($_thisQuery['having'])) {

                // Can't use Database::_implodeWithKeys, because the function
                // puts `` around the fieldname, causing it to treat the
                // aggregate function as a fieldname instead of a function
                $first = True;
                foreach ($_thisQuery['having'] as $key => $val) {
                    if($val !== '' and $val != null) {
                        if($first == False) {
                            $query .= ' AND ';
                        }
                        else {
                            $query .= ' HAVING ';
                        }
                        $first = False;

                        $query .= "$key LIKE " . $DB->quote("$val%");
                    }
                }
            }

            // apply ORDER BY filters
            $query .= " ORDER BY ";
            if (!empty($this->filter['order'])) {
                $query .= $this->filter['order']['field']." ".$this->filter['order']['fieldOrder'].", ";
            }
            $query .= $this->order_by;

            $debug=false;
            if ($debug)  print "<br> $vartype QUERY = <br> $query <br><hr><br>"; 

            // get the list
            $DB->select($query, $result);
            if(PEAR::isError($result)) {
                return PEAR::raiseError("DB Error: ".$result->getMessage());
            }

            // array merge to $_results 
            $_results = array_merge($result, $_results);

        } // end foreach variant type {CNV, SNP}

        $this->tpl_data['resultcount'] = sizeof($_results); 
        $this->tpl_data['variantFilter'] = $variantFilter; 
        $this->tpl_data['displayFilter'] = $displayFilter; 

        // $debug=true; 
        if ($debug) { print "<br> ### displayFilter = $displayFilter <br>"; }
       
        $debug=false;
        if ($debug) { 
           $sz = sizeof($_results); 
           print "<br><br> Query returns $sz rows : ===== <br>"; 
           print_r($_results); 
        }

        // return $result;
        return $_results;
    }

}
?>
