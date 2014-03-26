gewi Design
===========

gewi is intended to be pluggable, extensible, and easy to use.
As such it operates through several layers of abstraction, each
of which is vary loosely coupled to the others.

layout: This modules exports some tools for laying out the UI.
The main two modules this exports are the roout UI class and 
the UI container class that it is derived from.

interaction: This contains the base classes that allow for end
user interaction. Each of these installs a number of callbacks/
recieve methods that allow for various interactive methods.
The classes that are provided in this module are

    * Clickable: Any object that is clickable. Exports the following
      methods.
        * install_click_callback(callback function)
        * click()

render: This module contains various render methods for UI widgets.
For the most part these are relatively simple rendrers. Included 
renderers are:

    * TextRenderer: A simple base class for rendering text.
      Requires the utils/fontatlas class. Exports the following
      methods:
        * set_text/font/size
        * get_text/font/size
        * render
    * FlatRenderer: Exports a simple flat rendere that will
      render a box with a specific background color.
      
widgets: This module exports some core widgets that can later be
built upon and extended.
    
    * Screen Text: Uses the TextRenderer, and supports no interaction.
      This is a simple test to make sure text can be rendered properly.
    * Button: A simple clickable button. Embeds a container, so it should
      support text embedding.
      
      

UI Object: Represents and object in the UI
UI Root: A single special container
    
    
Layout and Styling
==================

I want to adopt an HTML/CSS style approach to styling/formating items. Perhaps
I'll take a subset of the standard CSS. Somethings I might want to suppot:

    * positioning keywords: float, absolute, relative
    * dimension keywords: width, height, minimum width/height
    * various units: %of parent, raw pixels
    
Should I extend this analogy and have each element be a container, with text as 
the leaves? How does this interact with acceleration structures?

All supported style attributes:

    * width: (value, units)
    * height: (value, units)
    * position: [absolute, static]
    * float: [left, right]
    * top: (value, units) { only really useful if postion is absolute } 
    * left: (value, units) { only really useful if postion is absolute } 

Valuse should be integers, units should be either PERCENT, PIXELS. By default,
all elements are assumed to have a width/height of 100%.

UIObject
--------

Attributes:

    * style attributes (perhaps stored as a map/unordered_map)
    * internal representation of width/height/x/y
    * root (perhaps for rendering acceleration)
    * matrix representing transformation/scaling
    * various callback methods
        * click callback
        * mouseover callback
        * key callback
    
Methods:
    
    * update_parent: Sets the parent, and updates anything on the back end that inherits
      from the parent.
        parent = new_parent
        
        If the width/height depend on the parent
            update width/height matrix
        If the position depended on the parent
            update the position matrix
        tell all chlidren that I've updated
        
    * render: Renders the actual UIObject (virtual)
        perform error checking
        upload model matrix;
        render mesh; 
        render children;
      An alterntavie method would be to keep a render queue in the root, so we don't have
      to thrash between shaders. Possible optimization.
    * click/mouseover/key: Checks if the object is currently selected/mouseover/etc. If this
      is the case it will call the callback. Recurses on children.
        
UIContainer
-----------

Basically just a non abstract version of a UIObject. Has no mesh, but will recursively render.

Button
------

Extends the UIObject by adding a simple rectangular mesh.

Text
----

Extends the UIObject, but requires a different renderer. Uses a font atlas to render text
to the screen.

A good resource is here http://www.html5rocks.com/en/tutorials/internals/howbrowserswork/