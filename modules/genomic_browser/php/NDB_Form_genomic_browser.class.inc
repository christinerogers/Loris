<?php

/**
 * form_genomic_browser class file
 *
 * PHP version 5
 * 
 * @category   Genomic
 * @package    Main
 * @subpackage Genomic 
 * @author     Loris team <info-loris.mni@mcgill.ca> 
 * @license    @GPLv3
 * @link       https://github.com/aces/Loris
*/

require_once "NDB_BVL_Battery.class.inc";
require_once 'NDB_Form.class.inc';
require_once 'GenomicFile.class.inc';
/**
 * NDB_Form_Genomic_Browser Class
 *
 * This class is genomic_browser Form
 * 
 * @category   Genomic
 * @package    Main
 * @subpackage Genomic 
 * @author     Loris team <info-loris.mni@mcgill.ca>
 * @license    @GPLv3
 * @link       https://github.com/aces/Loris
*/

class NDB_Form_Genomic_Browser extends NDB_Form
{
/**
 * vars to store the DCCID, sessionID, genomic file ID
*/
var $candID;
var $sessionID;
var $genomic_file_ID;

/**
* Determine whether the user has permission to view the genomic_browser_view_file page
*
* @return bool whether the user has access
*/
function _hasAccess()
{
    $user =& User::singleton();
    if (Utility::isErrorX($user)) {
        return PEAR::raiseError("User Error: " .$user->getMessage());
}

    // Add site control? See Imaging Browser example 

    return ($user->hasPermission('genomic_browser_view_allsites') || $user->hasPermission('genomic_browser_view_site'));
}

/**
* Sets up main parameters given one GenomicFileID
* Visit Label or SessionID not required
*
* @return NULL
*/
function viewGenomicFile() 
{
    $this->DB = Database::singleton();
    if (Utility::isErrorX($this->DB)) {
        print "Could not connect to database: ".$DB->getMessage()."<br>\n";
        die();
    }

    $this->genomic_file_ID = $_REQUEST['GenomicFileID'];
   //  $this->genomic_file_ID = $_REQUEST['GenomicFileID'];
    // if (!empty($this->genomic_file_ID) && is_numeric($this->genomic_file_ID)) {

    $this->candID = $_REQUEST['candID'];
    $this->category = $_REQUEST['Category'];

    if (!empty($this->candID) ) {
        // If saving any annotation changes, see imaging browser View Session 
        
        if (!empty($this->category) ) {
            $this->_setFileData($this->category); // FileData
        } 
        else { 
            $this->_setFileData(); // FileData
        }

        // for Session-specific information 
        // $this->tpl_data['headerTable'] = $this->getHeaderTable();

// not used: 

        $filename = $this->DB->pselectOne(
            "SELECT FileName FROM genomic_browser_files f 
              WHERE f.CandID=:cid ", 
            array('cid' =>$this->candID)
        );
        // ADD type condition! Raw vs. Cleaned  

        // no selected options defined
        $this->tpl_data['status_options'] 
          = array (''=>'&nbsp;', 'Pass'=>'Pass', 'Fail'=>'Fail');
        $this->tpl_data['caveat_options'] 
          = array ('' => '&nbsp;', true => 'True', false => 'False');
        $this->tpl_data['has_permission'] = ($this->_hasAccess()) ? true : false;
    }
}
/**
* Sets values for ONE file setFileData SINGULAR for Genomics
*
* @return NULL
*/
function _setFileData($category = null)  
{
    $extra_where_string = "";

    if (!empty($this->category) ) {
        $files = $this->DB->pselect(
            "SELECT genomic_browser_files.GenomicFileID FROM genomic_browser_files 
            WHERE CandID=:cid AND Category=:catid", 
            array(
            'cid' => $this->candID,
            'catid' => $this->category
            )
        );
    }
    else {
        $files = $this->DB->pselect(
            "SELECT genomic_browser_files.GenomicFileID FROM genomic_browser_files 
            WHERE CandID=:cid ", 
            array(
            'cid' => $this->candID
            )
        );
    }

// print_r($files); 

// get session ID? 

    $this->tpl_data['files'] = array();
    foreach ($files as $fileRow) {
        $FileObj = new GenomicFile($fileRow['GenomicFileID']);
        $file = array(
            'FileID'   => $fileRow['GenomicFileID'],
            'Filename' => basename($FileObj->getParameter('FileName')),
            'FullFilename' => $FileObj->getParameter('FileName'),
            'FilePackage' => $FileObj->getParameter('FilePackage'),
            'FileType' => $FileObj->getParameter('FileType'),
            'FileSize' => $FileObj->getParameter('FileSize'),
            'Description' => $FileObj->getParameter('Description'),
            'Category' => $FileObj->getParameter('Category'),
            // 'New' => ($FileObj->getParameter('QCFirstChangeTime') == '') ? 1 : 0,
            'Pipeline' => $FileObj->getParameter('Pipeline'),
            'Algorithm' => $FileObj->getParameter('Algorithm'),
            'Normalization' => $FileObj->getParameter('Normalization'),
            'SampleID' => $FileObj->getParameter('SampleID'),
            'Caveat' => $FileObj->getParameter('Caveat'),
            'Notes' => $FileObj->getParameter('Notes'),
            'AnalysisProtocol' => $FileObj->getParameter('AnalysisProtcol'),
            'AnalysisDate' => $this->_getDate(
                $FileObj, 'Date_taken', $analysisDate
            ), 
            'SampleDate' => $this->_getDate(
                $FileObj, 'Date_sample', $sampleDate
            ),
            'FileInsertDate' => $FileObj->getParameter('Date_inserted'),

            'Selected' => $FileObj->getParameter('Selected'),
            'QCStatus' => $FileObj->getParameter('QCStatus'),
            'QCDate' => $FileObj->getParameter('QCLastChangeTime'),
        );
        $this->tpl_data['files'][] = $file;
    }
}
/**
* Gets the date according to the type

######################
/**
* Sets up main parameters FOR ONE SESSION
*
* @return NULL
*/
function viewSession() 
{
    $this->DB = Database::singleton();
    if (Utility::isErrorX($this->DB)) {
        print "Could not connect to database: ".$DB->getMessage()."<br>\n";
        die();
    }

    $this->sessionID = $_REQUEST['sessionID'];

    if (!empty($this->sessionID) && is_numeric($this->sessionID)) {
        // If saving any changes, see imaging browser View Session 
        $this->_setFilesData();

        $this->tpl_data['headerTable'] = $this->getHeaderTable();

        $file = $this->DB->pselectOne(
            "SELECT File FROM files f 
              JOIN session s 
              ON (s.ID=f.SessionID) 
              WHERE s.ID=:sid AND FileType='obj'", 
            array('sid' =>$this->sessionID)
        );

        // no selected options defined
        $this->tpl_data['status_options'] 
          = array (''=>'&nbsp;', 'Pass'=>'Pass', 'Fail'=>'Fail');
        $this->tpl_data['caveat_options'] 
          = array ('' => '&nbsp;', true => 'True', false => 'False');
        $this->tpl_data['has_permission'] = ($this->_hasAccess()) ? true : false;
    }
}
/**
* Sets files values
*
* @return NULL
*/
function _setFilesData() 
{
    $extra_where_string = "";
    if (!empty($_REQUEST['selectedOnly'])) {
        $extra_where_string .= " AND COALESCE(sel.Value,'') <> ''";
    }

    $files = $this->DB->pselect(
        "SELECT files.FileID FROM files LEFT JOIN parameter_file as sel on (
        files.FileID=sel.FileID AND sel.ParameterTypeID=:selectedTypeID) 
        WHERE SessionID=:SID AND (AcquisitionProtocolID IS NULL 
        OR AcquisitionProtocolID not in (1, 2, 3, 52)) 
        AND PendingStaging=0 $extra_where_string 
        ORDER BY files.OutputType, sel.Value DESC, AcquisitionProtocolID",
        array(
        'SID' => $this->sessionID,
        'selectedTypeID' => $this->DB->selectOne(
        "SELECT ParameterTypeID 
        FROM parameter_type 
        WHERE Name='Selected' LIMIT 1"
        )
        )
    );
    $this->tpl_data['files'] = array();
    foreach ($files as $fileRow) {
        $FileObj = new MRIFile($fileRow['FileID']);
        if (empty($scannerID)) {
            $scannerID = $FileObj->getParameter('ScannerID');
            if (!empty($scannerID)) {
                $query = "SELECT 
                    CONCAT_WS(' ', Manufacturer, Model, Serial_number) 
                    FROM mri_scanner WHERE ID=:ScanID";
                $this->scanner = $this->DB->pselectOne(
                    $query, array('ScanID' => $scannerID)
                );
            }
        }
        $file = array(
            'FileID'   => $fileRow['FileID'],
            'Filename' => basename($FileObj->getParameter('File')),
            'CheckPic' => "/mri/jiv/get_file.php?file=pic/" 
                . $FileObj->getParameter('check_pic_filename'),
            'FullFilename' => $FileObj->getParameter('File'),
            'JivFilename' => basename($FileObj->getParameter('File')),
            'JivAddress' => str_replace(
                '_check.jpg', '', $FileObj->getParameter('check_pic_filename')
            ),
            'New' => ($FileObj->getParameter('QCFirstChangeTime') == '') ? 1 : 0,
            'Pipeline' => $FileObj->getParameter('Pipeline'),
            'OutputType' => $FileObj->getParameter('OutputType'),
            'AcquisitionProtocol' => $FileObj->getAcquisitionProtocol(),
            'CoordinateSpace' => $FileObj->getParameter('CoordinateSpace'),
            'Algorithm' => $FileObj->getParameter('Algorithm'),
            'AcquisitionDate' => $this->_getDate(
                $FileObj, 'acquisition_date', $acqDate
            ), 
            'ProcDate' => $this->_getDate(
                $FileObj, 'processing:processing_date', $procDate
            ),
            'FileInsertDate' => $FileObj->getParameter('InsertTime'),
            'SeriesDescription' => $FileObj->getParameter('series_description'),
            'SeriesNumber' => $FileObj->getParameter('series_number'),
            'EchoTime' => number_format(
                $FileObj->getParameter('echo_time')*1000, 2
            ),
            'RepetitionTime' => number_format(
                $FileObj->getParameter('repetition_time')*1000, 2
            ),
            'SliceThickness' => number_format(
                $FileObj->getParameter('slice_thickness'), 2
            ),
            'Time' => number_format($FileObj->getParameter('time'), 2),
            'Comment' => $FileObj->getParameter('Comment'),
            'ProcessingPipeline' => $FileObj->getParameter(
                'processing:pipeline'
            ),
            'TotalRejected' => $FileObj->getParameter(
                'processing:total_rejected'
            ),
            'SourceFile' => basename(
                $FileObj->getParameter('processing:sourceFile')
            ),
            'Tool' => $FileObj->getParameter('Tool'),
            'InterlaceRejected' => $this->_getRejected(
                    $FileObj, 'interlace', $laceRej
            ),
            'IntergradientRejected' => $this->_getRejected(
                    $FileObj, 'intergradient', $interRej
            ), 
            'Xstep' => number_format($FileObj->getParameter('xstep'), 2),
            'Ystep' => number_format($FileObj->getParameter('ystep'), 2),
            'Zstep' => number_format($FileObj->getParameter('zstep'), 2),
            'Selected' => $FileObj->getParameter('Selected'),
            'QCStatus' => $FileObj->getParameter('QCStatus'),
            'QCDate' => $FileObj->getParameter('QCLastChangeTime'),
            'Caveat' => $FileObj->getParameter('Caveat'),
            'SeriesUID' => $FileObj->getParameter('SeriesUID'),
            'XMLreport' => $FileObj->getParameter('processing:DTIPrepXmlReport'),
            'XMLprotocol' => $FileObj->getParameter('ProtocolFile'),
            'NrrdFile' => $FileObj->getParameter('processing:nrrd_file')
        );
        $this->tpl_data['files'][] = $file;
    }
}
/**
* Gets the date according to the type
* 
* @param MRIFile $file  file object 
* @param string  $type  type of the date
* @param array   $array array containing the date
*
* @return date if exists, if not an empty string
*/
function _getDate($file, $type, $array)
{
if (preg_match(
"/(\d{4})-?(\d{2})-?(\d{2})/", 
$file->getParameter($type), $array
)) {
return (mktime(12, 0, 0, $array[2], $array[3], $array[1]));
} else {
return "";
} 
}

/**
* Gets header table html
*
* @return $html of the header table
*/
function getHeaderTable() 
{
$tpl_data = array();
$tpl_data['subject'] = $this->getSubjectData();

if (!empty($_REQUEST['outputType'])) {
$tpl_data['outputType'] = urldecode($_REQUEST['outputType']);
}
$config = NDB_Config::singleton();
if ($config->getSetting('useEDC') === 'true') {
$tpl_data['useEDC'] = true;
}

$smarty = new Smarty_neurodb('imaging_browser');

$smarty->assign($tpl_data);
$html = $smarty->fetch("table_session_header.tpl");
return $html;
}
/**
* Populates data for the template
*
* @return $subjectData array with data
*/
function getSubjectData() 
{
$timePoint =& TimePoint::singleton($_REQUEST['sessionID']);
if (Utility::isErrorX($timePoint)) {
print $timePoint->getMessage()."<br>";
}

$subjectData['sessionID'] = $_REQUEST['sessionID'];
$subjectData['SubprojectID'] = $timePoint->getSubprojectID();
$subjectData['SubprojectTitle'] = $timePoint->getData('SubprojectTitle');
$subjectData['visitLabel'] = $timePoint->getVisitLabel();
$subjectData['visitNo'] = $timePoint->getVisitNo();
$subjectData['site'] = $timePoint->getPSC();
$qcstatus = $this->DB->pselectRow(
"SELECT MRIQCStatus, MRIQCPending 
FROM session WHERE ID=:SID", 
array('SID' => $_REQUEST['sessionID'])
);
$subjectData['mriqcstatus'] = $qcstatus['MRIQCStatus'];
$subjectData['mriqcpending'] = $qcstatus['MRIQCPending'];
$subjectData['candid'] = $timePoint->getCandID();
$subjectData['scanner'] = $this->scanner;
$candidate =& Candidate::singleton($timePoint->getCandID());
if (Utility::isErrorX($candidate)) { 
print $candidate->getMessage()."<br>";
} else {
$subjectData['pscid'] = $candidate->getPSCID();
$subjectData['dob'] = $candidate->getCandidateDoB();
$subjectData['edc'] = $candidate->getCandidateEDC();
$subjectData['gender'] = $candidate->getCandidateGender();

// This doesn't work. 
//Need to find the proper way to get the TarchiveID. 
//It should be per file, not per candidate. --Dave
$params = array();
$EntityType = $candidate->getData('Entity_type');
if ($EntityType == 'Scanner') {
$ID = ":PPSCID";
$params['PPSCID'] = $timePoint->getData('PSCID');
} else {
$ID = "LOWER(CONCAT(:PPSCID, '_', :PCandID, '_', :PVL, '%'))";
$params['PPSCID'] = $candidate->getPSCID();
$params['PCandID'] = $timePoint->getCandID();
$params['PVL'] = $timePoint->getVisitLabel();
}
$tarchiveIDs = $this->DB->pselect(
"SELECT TarchiveID 
FROM tarchive 
WHERE PatientName LIKE $ID", $params
);
$subjectData['tarchiveids'] = $tarchiveIDs;
}
  // Cache the data
  return $subjectData;
}

}
?>
