
--
-- Table structure for table `GWAS`
--

DROP TABLE IF EXISTS `GWAS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `GWAS` (
  `GWASID` bigint(20) NOT NULL AUTO_INCREMENT,
  `SNPID` bigint(20) NOT NULL,
  `rsID` varchar(20) DEFAULT NULL,
  `Chromosome` varchar(9) DEFAULT NULL,
  `Position_BP` varchar(20) DEFAULT NULL,
  `MajorAllele` enum('A','C','T','G') DEFAULT NULL,
  `MinorAllele` enum('A','C','T','G') DEFAULT NULL,
  `MAF` varchar(20) DEFAULT NULL,
  `Estimate` varchar(20) DEFAULT NULL,
  `StdErr` varchar(20) DEFAULT NULL,
  `Pvalue` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`GWASID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Stores results of Genome-Wide Analysis Study';



--
-- Table structure for table `SNP_candidate_rel`
--

DROP TABLE IF EXISTS `SNP_candidate_rel`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SNP_candidate_rel` (
  `SNPID` bigint(20) NOT NULL DEFAULT '0',
  `CandID` varchar(255) NOT NULL DEFAULT '0',
  `ArrayReport` enum('Normal','Uncertain','Pending') DEFAULT NULL,
  `ArrayReportDetail` varchar(255) DEFAULT NULL,
  `ValidationMethod` varchar(50) DEFAULT NULL,
  `Validated` enum('0','1') DEFAULT NULL,
  `GenotypeQuality` int(4) DEFAULT NULL,
  `PlatformID` bigint(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `SNP_attribute`
--

DROP TABLE IF EXISTS `SNP_attribute`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SNP_attribute` (
  `SNPID` bigint(20) NOT NULL AUTO_INCREMENT,
  `rsID` varchar(9) DEFAULT NULL,
  `Description` text,
  `SNPExternalName` varchar(255) DEFAULT NULL,
  `SNPExternalSource` varchar(255) DEFAULT NULL,
  `ObservedBase` enum('A','C','T','G') DEFAULT NULL,
  `ReferenceBase` enum('A','C','T','G') DEFAULT NULL,
  `Markers` varchar(255) DEFAULT NULL,
  `FunctionPrediction` enum('exonic','ncRNAexonic','splicing','UTR3','UTR5') DEFAULT NULL,
  `Damaging` enum('D','NA') DEFAULT NULL,
  `ExonicFunction` enum('nonsynonymous','unknown') DEFAULT NULL,
  `GenomeLocID` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`SNPID`),
  KEY `GenomeLocID` (`GenomeLocID`)
) ENGINE=MyISAM AUTO_INCREMENT=154 DEFAULT CHARSET=latin1;

--
-- Table structure for table `genomic_browser_files`
--

DROP TABLE IF EXISTS `genomic_browser_files`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `genomic_browser_files` (
  `GenomicFileID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `CandID` int(6) NOT NULL DEFAULT '0',
  `VisitLabel` varchar(255) DEFAULT NULL,
  `FileName` varchar(255) NOT NULL,
  `FilePackage` tinyint(1) DEFAULT NULL,
  `Description` varchar(255) NOT NULL,
  `FileType` varchar(255) NOT NULL,
  `FileSize` bigint(20) NOT NULL,
  `Platform` varchar(255) DEFAULT NULL,
  `Batch` varchar(255) DEFAULT NULL,
  `Source` varchar(255) DEFAULT NULL,
  `Date_taken` date DEFAULT NULL,
  `Category` enum('raw','cleaned','GWAS') DEFAULT NULL,
  `Pipeline` varchar(255) DEFAULT NULL,
  `Algorithm` varchar(255) DEFAULT NULL,
  `Normalization` varchar(255) DEFAULT NULL,
  `SampleID` varchar(255) DEFAULT NULL,
  `AnalysisProtocol` varchar(255) DEFAULT NULL,
  `InsertedByUserID` varchar(255) NOT NULL DEFAULT '',
  `Date_inserted` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `Caveat` tinyint(1) DEFAULT NULL,
  `Notes` text,
  PRIMARY KEY (`GenomicFileID`),
  KEY `FK_genomic_browser_files_1` (`CandID`),
  CONSTRAINT `FK_genomic_browser_files_1` FOREIGN KEY (`CandID`) REFERENCES `candidate` (`CandID`)
) ENGINE=InnoDB AUTO_INCREMENT=43 DEFAULT CHARSET=utf8;


INSERT INTO SNP_attribute (SNPID, rsID, Description, SNPExternalName, SNPExternalSource, ObservedBase, ReferenceBase, Markers, FunctionPrediction, Damaging, ExonicFunction, GenomeLocID)  SELECT DISTINCT (SNPID, rsID, Description, SNPExternalName, SNPExternalSource, ObservedBase, ReferenceBase, Markers, FunctionPrediction, Damaging, ExonicFunction, GenomeLocID) FROM SNP;

INSERT INTO SNP_candidate_rel (SNPID, CandID, ArrayReport, ArrayReportDetail, ValidationMethod, Validated, GenotypeQuality, PlatformID)  SELECT DISTINCT (SNPID, CandID, ArrayReport, ArrayReportDetail, ValidationMethod, Validated, GenotypeQuality, PlatformID) FROM SNP;

DROP TABLE IF EXISTS `SNP`;
