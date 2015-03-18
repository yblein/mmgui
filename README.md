# MapMaker GUI
A small GUI to generate maps using the [MapMaker library](https://github.com/jube/mapmaker).

## Building
Edit the location of MapMaker in [mmgui.pro](./mmgui.pro). Then simply run

    qmake
    make

## TODO
* Node deletion (contextual menu?)
* Configuration UI for filters
* Mutiple outputs
* Textual outputs
* Default scene
* Complete generators
* Complete filters
* Add multi-input filters (filter `shader`)
* Improve initial positioning of nodes
* Ensure memory sanity
* Realtime update when changing settings
    * might be too expensive?
    * turn on/off according to map size/computation time?
* Size independant?

## Authors
- Yoann Blein
