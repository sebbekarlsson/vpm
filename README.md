# VPM
> Vim Plugin Manager

<div width='100%' style='text-align: center; width: 100%;' align='center'>
    <img src='tty.gif'/>
</div>

## Install plugins the easy way
> Think of `vpm` as a package manager like `npm` or `apt` or `pacman`.  
> You can use it to __install__ plugins like this:

    vpm install 'easymotion/vim-easymotion'

> And the plugin will be downloaded and installed for your vim configuration.  
> You can also __uninstall__ plugins like this:

    vpm uninstall 'easymotion/vim-easymotion'

> And the plugin will be removed.

## Installation
> To install `vpm`, simply clone down this repository and inside; run:

    make
    sudo make install

> Now, create these directories and put your plugins in this file:

    $HOME/.vim/vpm/sources.vim
    
> _(Create the directories if they do not already exist)_  
> Done!
