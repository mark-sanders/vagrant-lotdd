# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure(2) do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://atlas.hashicorp.com/search.
  config.vm.box = "ubuntu/trusty64"

  # THE URL FROM WHERE THE 'CONFIG.VM.BOX' BOX WILL BE FETCHED IF IT
  # DOESN'T ALREADY EXIST ON THE USER'S SYSTEM.
  config.vm.box_url = "http://cloud-images.ubuntu.com/vagrant/trusty/current/trusty-server-cloudimg-amd64-vagrant-disk1.box"

  if Vagrant.has_plugin?("vagrant-timezone")
    config.timezone.value = "Europe/London"
  end

  if Vagrant.has_plugin?("vagrant-proxyconf")
    config.proxy.http     = "http://85.115.60.150:8089"
    config.proxy.https    = "http://85.115.60.150:8089"
    config.proxy.no_proxy = "localhost,127.0.0.1"
  end

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  # config.vm.box_check_update = false

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # config.vm.network "forwarded_port", guest: 80, host: 8080

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  config.vm.provider "virtualbox" do |vb|
    # Customize the amount of memory on the VM:
    vb.memory = "1024"
  end
  
  # Enable provisioning with a shell script. Additional provisioners such as
  # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
  # documentation for more information about their specific syntax and use.
  config.vm.provision "shell", inline: <<-SHELL
    sudo apt-get update
    sudo apt-get upgrade
    sudo apt-get install -y build-essential
    sudo apt-get install -y git
    sudo apt-get install -y cmake
    sudo apt-get install -y unzip

    # install cpputest package instead of building it
    sudo apt-get install -y cpputest

    # add environment variables if not added
    if ! grep -q "GMOCK_HOME" /home/vagrant/.profile; then
      echo "" >> /home/vagrant/.profile
      echo "# set Google Mock home" >> /home/vagrant/.profile
      echo "export GMOCK_HOME=~/tools/gmock-1.6.0" >> /home/vagrant/.profile
    fi

#    if ! grep -q "CPPUTEST_HOME" /home/vagrant/.profile; then
#      echo "" >> /home/vagrant/.profile
#      echo "# set CppUTest home" >> /home/vagrant/.profile
#      echo "export CPPUTEST_HOME=~/tools/cpputest-3.3" >> /home/vagrant/.profile
#    fi

  SHELL

  # provisioning with a non-privileged shell script i.e. as vagrant user
  $script = <<-SCRIPT
    # create temp directory
    if [ ! -d ~/temp ] 
    then
      mkdir ~/temp
    fi
    # create tools directory
    if [ ! -d ~/tools ] 
    then
      mkdir ~/tools
    fi

    # download Google Mock v1.6.0
    if [ ! -f ~/temp/gmock-1.6.0.zip ]
    then
      wget -q -P ~/temp https://googlemock.googlecode.com/files/gmock-1.6.0.zip
    fi

    # unzip Google Mock under tools directory
    if [ ! -d ${GMOCK_HOME} ]
    then
      unzip -d ~/tools ~/temp/gmock-1.6.0.zip
    fi

    # build Google Mock
    if [ ! -d ${GMOCK_HOME}/mybuild ]
    then
      mkdir ${GMOCK_HOME}/mybuild
      
      cd ${GMOCK_HOME}/mybuild
      cmake ..
      make
    fi

    # build Google Test
    if [ ! -d ${GMOCK_HOME}/gtest/mybuild ]
    then
      mkdir ${GMOCK_HOME}/gtest/mybuild

      cd ${GMOCK_HOME}/gtest/mybuild
      cmake ..
      make
    fi


  SCRIPT

  config.vm.provision "shell", inline: $script, privileged: false

end
