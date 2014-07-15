name = 'Apple'
description = "It looks shiny and delicous!"
location = 'room2:2:room3:1'
obtainable = '1'
visible = '1'

function onUse(command)
  if te:playerHasItem("Apple") then
    te:playerRemoveItem("Apple", 1);
  else
    te:roomRemoveItem("Apple", 1, te:getCharacterLocation("player"));
  end
  te:addMessage("YUM! That's one of the best apples you have ever had!\n");
  te:setPlayerHealth(te:getPlayerHealth() + 1);
end

function onHelp()
  te:addMessage("It's an apple, just use it");
end

