# sysshell
sysshell is a generic shell for wayland written in gtkmm 4<br>
This program serves as a launcher for my other sys* programs and doesn't offer any additional features (yet)<br>

# Features
## [sysbar](https://github.com/System64fumo/sysbar)
Modular status bar for wayland written in gtkmm4<br>
![preview](https://github.com/System64fumo/sysbar/blob/main/preview.jpg "preview")

## [sysboard](https://github.com/System64fumo/sysboard)
Simple virtual keyboard for wayland<br>
![preview](https://github.com/System64fumo/sysboard/blob/main/preview.png "preview")

## [syshud](https://github.com/System64fumo/syshud)
Simple system status indicator written in gtkmm 4<br>
![preview](https://github.com/System64fumo/sysvol/blob/main/preview.gif "preview")

## [syslock](https://github.com/System64fumo/syslock)
Simple screen locker for wayland written in gtkmm 4<br>
![preview](https://github.com/System64fumo/syslock/blob/main/preview.gif "preview")

## [sysmenu](https://github.com/System64fumo/sysmenu)
Simple and efficient application launcher written in gtkmm4<br>
![default](https://github.com/System64fumo/sysmenu/blob/main/preview_default.gif "default")

## [syspower](https://github.com/System64fumo/syspower)
Simple power menu/shutdown screen written in gtkmm 4<br>
![default](https://github.com/System64fumo/syspower/blob/main/preview.gif "preview")


# Signals
Use the following signals to perform the corresponding actions.<br>
`pkill -10` sysmenu: Show window<br>
`pkill -12` sysmenu: Hide window<br>
`pkill -34` sysmenu: Toggle window<br>
`pkill -35` syslock: Lock screen<br>
`pkill -36` sysbar: Show window<br>
`pkill -37` sysbar: Hide window<br>
`pkill -38` sysbar: Toggle window<br>
`pkill -39` syspower: Show window<br>
`pkill -40` sysboard: Show window<br>
`pkill -41` sysboard: Hide window<br>
`pkill -42` sysboard: Toggle window<br>
`pkill -43` clipboard: Show window<br>


## Clipboard
Simple clipboard history manager<br>
This is the first exclusive feature, To enable it add `extras=clipboard` to your config.<br>
Please do note!! This feature is still experimental and thus lacking features.<br>
Additionally, Your clipboard gets copied to a temporary file (That gets deleted a few ms later) so it's sort of insecure.<br>

# Why does this exist?
Launching individual sysshell components consumes a lot of resources, Especially when hardware acceleration is enabled.<br>
So launching everything from one GTK Application instance helps mitigate the increased memory usage at the cost of stability.<br>
(If one program crashes the whole shell goes down with it)<br>

# Contribution
This is my most ambitious project yet and i'm unsure if i'm capable of finishing anything i've started.<br>
If you wish for a feature to be added/fixed/worked on please open an issue, I prefer focusing on what annoys me or others first.<br>
Additionally, Any kind of contribution is welcome be it documentation, code, cleanup, etc.<br>

# Packaging
I package my software on the AUR, However some parts of my software also exists on other repositories maintained by the community.<br>
Maintaining packages for every distribution out there sounds like a lot of work, So if you'd like to feel free to package and maintain any of my projects on your repo of choice.<br> (Please open an issue so i can keep track of what exists where, I'd like to eventually have a list in the project's repos)

# Future plans
Create a screenshot overlay<br>
Create a polkit/keyring overlay<br>
Optimize existing stuff as much as possible, At the moment the focus is on features<br>
Either rewrite major sections of code with more up to date C++ practices/stuff or rewrite in pure C<br>
Split/Handle shared code via a common library to reduce duplicate code<br>

# License
My software is typically licensed under the WTFPL license, Not a perfect license but it gets the job done.<br>
I grant you permission to do practically anything with my software, All i ask in exchange is to be credited.<br>
