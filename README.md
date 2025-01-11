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
Primarily because i wanted to have some fun writing a shell, But also because other solutions don't quite do a good enough job for me<br>
The sysshell launcher exists as a way to preserve memory instead of launching every sys* program independently.<br>
This is one of my most ambitious projects yet and i'm unsure if i'm capable of finishing everything i've started,
Contribution is most certianly welcome!

# Future plans
Create a screenshot overlay<br>
Create a polkit/keyring overlay<br>
Optimize existing stuff as much as possible, At the moment the focus is on features<br>
Either rewrite major sections of code with more up to date C++ practices/stuff or rewrite in pure C<br>
Split/Handle shared code via a common library to reduce duplicate code<br>

