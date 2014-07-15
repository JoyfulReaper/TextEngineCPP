name = 'Broken Pen'
description = "It's a broken pen. I doubt it would write very well..."
location = 'room1:1'
obtainable = '1'
visible = '1'

function onUse(command)
  te:addMessage("You try writing with it but it doesn't seem to work.\n");
end

function onHelp()
  te:addMessage("No special paramaters, just use it!\n");
end
