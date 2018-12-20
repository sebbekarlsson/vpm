# VPM
> Vim Plugin Manager

<div width='100%' style='text-align: center; width: 100%;' align='center'>
    <img src='gif.gif'/>
</div>

## Install plugins the easy way
> Think of `vpm` as a package manager like `npm` or `apt` or `pacman`.  
> You can use it to __install__ plugins like this:

    vpm install 'easymotion/vim-easymotion'

> And the plugin will be downloaded and installed for your vim configuration.  
> You can also __uninstall__ plugins like this:

    vpm uninstall 'easymotion/vim-easymotion'

> And the plugin will be removed.

## List installed plugins
> You can also list currently installed plugins using the `list` command:

    vpm list plugins

    ...

## Installation
> To install `vpm`, simply clone down this repository and inside; run:

    make
    sudo make install

> Now, create these directories and put your plugins in this file:

    $HOME/.vim/vpm/sources.vim
    
> _(Create the directories if they do not already exist)_  

> You will also need to `source` the file above in your `.vimrc` config file.

> Done!

## Notes
> `vpm` currently only supports `Vundle` , but pull-requests are welcome, so
> if you are using any other package manager for ViM, create a pull-request
> for it :)

## Technical notes
### The _list_ command
> The `list` command is basically just dumping the contents of your `sources.vim` file.

### The _install_ command
> The `install` command just adds a new line to your `sources.vim` file.

### The _uninstall_ command
> The `uninstall` command basically just removes the line matching the specified
> plugin in your `sources.vim` file.

### The _install/uninstall_ GUI
> The install/uninstall GUI just uses the GUI that your current plugin manager uses,
> so right now it is using the one that comes with `Vundle`.
