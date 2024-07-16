# sysshell
sysshell is a generic shell for wayland written in gtkmm 4<br>
This program serves as a launcher for my other sys* programs and doesn't offer any additional features (yet)<br>

# Features
[sysbar](https://github.com/System64fumo/sysbar) Modular status bar for wayland<br>
[syshud](https://github.com/System64fumo/syshud) Simple heads up display written in gtkmm 4<br>
[sysmenu](https://github.com/System64fumo/sysmenu) Simple program launcher written in gtkmm 4<br>

# Why does this exist?
I was rather annoyed by how much memory GTK guzzled up,<br>
So i decided to convert my sys* programs to libraries that could be loaded via sysshell which would significantly reduce their memory footprint.

# Future plans
I kind of want to share more stuff between the programs to hopefully reduce memory usage and possibly disk usage a bit more.<br>
An example would be syshud and sysbar's volume monitor.
