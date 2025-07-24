# sysshell
sysshell is a generic shell meant to provide a cohesive experience for all.<br>
It's also a personal project so goals and features may cator to my requirements.<br>

# Features
## [sysbar](https://github.com/System64fumo/sysbar)
Modular status bar<br>
<img src="https://github.com/System64fumo/sysbar/blob/main/preview.jpg" alt="preview" width="720">

## [sysboard](https://github.com/System64fumo/sysboard)
Simple virtual keyboard<br>
<img src="https://github.com/System64fumo/sysboard/blob/main/preview.png" alt="preview" width="720">

## [syshud](https://github.com/System64fumo/syshud)
Simple system status indicator<br>
<img src="https://github.com/System64fumo/syshud/blob/main/preview.gif" alt="preview">

## [syslock](https://github.com/System64fumo/syslock)
Simple screen locker<br>
<img src="https://github.com/System64fumo/syslock/blob/main/preview.gif" alt="preview" width="720">

## [sysmenu](https://github.com/System64fumo/sysmenu)
Simple and efficient application launcher<br>
<img src="https://github.com/System64fumo/sysmenu/blob/main/preview_default.gif" alt="preview" width="720">

## [syspower](https://github.com/System64fumo/syspower)
Simple power menu/shutdown screen<br>
<img src="https://github.com/System64fumo/syspower/blob/main/preview.gif" alt="preview" width="720">


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
The sysshell binary exists as a way to reduce resource consumption as launching several application instances tends to consume more memory.<br>
The shell components exist because there wasn't cohesive DE agnostic graphical shell out there that did things the way i wanted.<br>
Also because i wanted to have the control and flexibility of having my own shell.<br>

# Contribution
This is my most ambitious project yet and i'm unsure if i'm capable of finishing anything i've started.<br>
If you wish for a feature to be added/fixed/worked on please open an issue, I prefer focusing on what annoys me or others first.<br>
Additionally, Any kind of contribution is welcome be it documentation, code, cleanup, etc.<br>

# Packaging
I package my software on the AUR, However some parts of my software also exists on other repositories maintained by the community.<br>
Maintaining packages for every distribution out there sounds like a lot of work, So if you'd like to feel free to package and maintain any of my projects on your repo of choice.<br> (Please open an issue so i can keep track of what exists where, I'd like to eventually have a list in the project's repos)

# GNOME/GTK
Unfortunately the GNOME foundation is not the best.. And their decisions often leaves people divided such as with GTK5 and Libadwaita.<br>
I've attempted to rewrite the shell in QT but quickly found out that it's not a serious alternative to GTK..<br>
If you take issue with GNOME's direction, leadership, politics or GTK and want to avoid it wherever possible i suggest you take a look at [Quickshell](https://quickshell.org/).<br>

# Future plans
Create a screenshot overlay<br>
Create a polkit/keyring overlay<br>
Optimize existing stuff as much as possible, At the moment the focus is on features<br>
Split/Handle shared code via a common library to reduce duplicate code<br>
Possibly rewrite some code in pure C to reduce complexity and compile time?<br>

# License
My software is typically licensed under WTFPL but will be replaced by GPL in the near future.<br>
I grant you permission to do practically anything with my software, All i ask in exchange is to be credited.<br>
