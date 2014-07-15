shortName = 'room1'
name = 'Testing Room 1'
description = [[You awake with a splitting headache. You find that your legs are weak and that you must stand up slowly or risk collapsing back onto the cold damp floor.]]
lookDescription = "You squint really carefully, but the room is still dark. You can just barely make out an exit or two"
exits = 'N:room2:S:room3'
startRoom = '1'

function onEnter ()
  te:addMessage("This is a test from onEnter\n\n");
  te:runScript("test.lua");
  if te:getRoomVisited("room1") then
    te:setRoomDescription("WHO DUDE! THE DESCRIPTION OF THIS ROOM CHANGED! How freaking crazy is that?", "room1");
  end
end
