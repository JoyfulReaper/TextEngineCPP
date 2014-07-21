shortName = 'room0'
name = 'Entry Hall'
description = [[You awake in a dimly lit entry hall with no recollection of how you got there. You really should stop drinking so much...]]
lookDescription = [[The hall is dim, lit only with a couple of torches set firmly in the wall. There are some red and gold banners hanging from the walls. There is a large set of doors behind you and a door in front of you and to your left]]
exits = 'N:room1:E:room3:SL:roomwin'
startRoom = '1'

function onEnter ()
  if te:getRoomVisited("room0") then
    te:setRoomDescription([[The hall is still the same. The torches gutter every now and then in the damp drafts that blow through the building.]], "room0");
  end
end
