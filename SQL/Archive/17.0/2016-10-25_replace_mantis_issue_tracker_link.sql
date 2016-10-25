--- rename mantis_url ConfigSetting to issue_tracker_url
UPDATE ConfigSettings SET Name="issue_tracker_url", Description="Default: Issue Tracker module URL. Customize this if using external bug tracking software", Label="Issue Tracker URL" WHERE Name="mantis_url";

--- if never used, insert into Config table and populate with Issue Tracker module url
INSERT INTO Config 
     (Value, SET Value = CONCAT(SELECT Value FROM Config 
                           WHERE ConfigID=(SELECT ID FROM ConfigSettings WHERE Name='url'), 
                        '/issue_tracker/'), 
     WHERE NOT EXISTS (SELECT * FROM Config WHERE ConfigID=(SELECT ID FROM ConfigSettings WHERE Name='issue_tracker_url')
);

--- if blank, set Issue Tracker module url value for this config setting
UPDATE Config SET Value = CONCAT(SELECT Value FROM Config 
                                    WHERE ConfigID=(SELECT ID FROM ConfigSettings WHERE Name='url'), 
                        '/issue_tracker/'),
       WHERE Value = '' AND ConfigID= (SELECT ID FROM ConfigSettings WHERE Name='issue_tracker_url')


