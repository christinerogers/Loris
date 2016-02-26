--
-- Table structure for table `SNP_candidate_rel`--

DROP TABLE IF EXISTS `SNP_candidate_rel`;
CREATE TABLE `SNP_candidate_rel` (
  `SNPID` int(20) NOT NULL DEFAULT '0',
  `CandID` varchar(255) NOT NULL DEFAULT '0',
  `ObservedBase` enum('A','C','T','G') DEFAULT NULL,
  `ArrayReport` enum('Normal','Uncertain','Pending') DEFAULT NULL,
  `ArrayReportDetail` varchar(255) DEFAULT NULL,
  `ValidationMethod` varchar(50) DEFAULT NULL,
  `Validated` enum('0','1') DEFAULT NULL,
  `GenotypeQuality` int(4) DEFAULT NULL,
  `PlatformID` int(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO SNP_candidate_rel (SNPID, CandID, ObservedBase, ArrayReport, ArrayReportDetail, ValidationMethod, Validated, GenotypeQuality, PlatformID)  SELECT DISTINCT (SNPID, CandID, ObservedBase, ArrayReport, ArrayReportDetail, ValidationMethod, Validated, GenotypeQuality, PlatformID) FROM SNP;

ALTER TABLE SNP DROP COLUMN ObservedBase, ArrayReport, ArrayReportDetail, ValidationMethod, Validated, GenotypeQuality, PlatformID;  
