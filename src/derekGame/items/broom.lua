name = 'Broom'
description = "It's a broom. Nothing special about it. Unless you have some sort of broom fetish... You probably can't fly on it either."
location = 'room3:1'
obtainable = '1'
visible = '1'

function onUse(command)
  te:addMessage("You put the broom between your legs and jump...and promptly fall back to the floor.\n");
end

function onHelp()
  te:addMessage("If you need help using a broom, you must not be too bright.\n");
end
