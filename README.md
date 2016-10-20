#LORIS Neuroimaging Platform [![Build Status](https://travis-ci.org/aces/Loris.svg?branch=16.1-dev)](https://travis-ci.org/aces/Loris)

LORIS (Longitudinal Online Research and Imaging System) is a web-based data and project management software for neuroimaging research. LORIS makes it easy to manage large datasets including behavioural, clinical, neuroimaging and genetic data acquired over time or at different sites.

<hr>
NEW <b>⇾  Try LORIS on Heroku</b> before installing it on your system<br>
Test out the project management and clinical data management side of LORIS (complete Imaging features not yet available)<br>
Deploy and log in with username <i>admin</i> and the password that's set up during deployment via ClearDB.
[![Deploy](https://www.herokucdn.com/deploy/button.png)](https://heroku.com/deploy?template=https://github.com/aces/Loris/tree/17.0-dev)
<hr>

This Readme covers installation the <b>17.1</b> LORIS development branch on <b>Ubuntu</b>.
([CentOS Readme also available](https://github.com/aces/Loris/blob/16.1-dev/README.CentOS6.md)).

If you are looking to install a stable release, please consult the [Releases page](https://github.com/aces/Loris/releases) and the Readme for the last stable release.

Please consult the [LORIS Wiki Setup Guide](https://github.com/aces/Loris/wiki/Setup) notes on this [Install process](https://github.com/aces/Loris/wiki/Install-Script) for more information not included in this Readme. The [LORIS Developers mailing list](http://www.bic.mni.mcgill.ca/mailman/listinfo/loris-dev) may also provide installation guidance not covered in the Wiki. 

# Prerequisites for Installation

 * LINUX (supported on Ubuntu 14.04 and 16.04 and [CentOS 6.5](https://github.com/aces/Loris/blob/16.1-dev/README.CentOS6.md))
 * Apache2 
 * MySQL 5.7 
 * PHP <b>7</b> )
 * Package manager (for LINUX distributions)
 * Composer : should be run with --no-dev option

 Important: run Composer should be run with --no-dev option unless you are an active LORIS developer. 

Consult the [LORIS Wiki](https://github.com/aces/Loris/wiki/Setup) page on this [Install process](https://github.com/aces/Loris/wiki/Install-Script) for more information.

# Installation

Installation is now performed via the web-based Install process.  For installation of the last release, please see the Readme for https://github.com/aces/Loris/master

1. Set up LINUX user lorisadmin and create LORIS base directory:

    ```
    sudo useradd -U -m -G sudo -s /bin/bash lorisadmin
    sudo passwd lorisadmin
    su - lorisadmin
    ```

    <b>Important ⇾ All steps from this point forward must be executed by lorisadmin user</b>

    ```
    sudo mkdir -m 775 -p /var/www/$projectname
    sudo chown lorisadmin.lorisadmin /var/www/$projectname
    ```

    <i>$projectname ⇾ "loris" or one-word project name</i>

2. Get code:
    Download the latest release from the [releases page](https://github.com/aces/Loris/releases) and
    extract it to `/var/www/$projectname`

3. Run installer script to install core code, and libraries. The script will prompt for information and so that it can create directories automatically.

    For more information, please read the [Install Script wiki page](https://github.com/aces/Loris/wiki/Install-Script).

    ```
    cd /var/www/$projectname/tools
    ./install.sh
    ```

4. Apache configuration and restart 
LORIS requires Apache's mod_rewrite module to rewrite its URLs. Enable this module, then restart Apache: 

    ```
    sudo a2enmod rewrite
    sudo service apache2 reload
    ```

5. Go to http://localhost/installdb.php and follow the instructions to finalize LORIS installation.

    ```
    sudo a2dissite default
    sudo a2ensite $projectname
    sudo service apache2 reload
    ```

6. Follow the [Setup Guide in the LORIS Wiki](https://github.com/aces/Loris/wiki/Setup) to complete your post-installation setup and configuration, and for more documentation.

# Community
Please feel free to subscribe to the [LORIS Developers mailing list](http://www.bic.mni.mcgill.ca/mailman/listinfo/loris-dev) to ask any LORIS-related questions.
