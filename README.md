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

