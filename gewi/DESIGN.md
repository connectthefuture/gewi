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
        