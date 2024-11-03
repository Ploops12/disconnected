#pragma once

#include <string>
#include <unordered_map>

enum class TutorialState {
	START_1 = 0,
	START_2,
	LIGHT,
	CONNECT_1,
	SWITCH_TOP,
	CALLER_1,
	RESPONSE_1,
	LOOKUP_1,
	LOOKUP_2,
	LOOKUP_3,
	CONNECT_2,
	SWITCH_BTM,
	RINGING,
	RESPONSE_2,
	PICKUP_1,
	PICKUP_2,
	CALLER_2,
	SWITCH_MID,
	WAITING_1,
	WAITING_2,
	WAITING_3,
	WAITING_4,
	WAITING_5,
	WAITING_6,
	DISCONNECT,
	FINISH_1,
	FINISH_2,
	FINISH_3,
	FINISH_4,
	FINISH_5,
	FINISH_6,
	END,
	GAME_OVER
};

struct Message {
	std::string speaker;
	std::string text;
};

std::unordered_map<TutorialState, Message> tutorialMessages{
	{TutorialState::START_1, {"MANAGEMENT", "Welcome new phone operator to Talkutronix!"}},
	{TutorialState::START_2, {"MANAGEMENT", "Since this is your first day on the job, let's walk you through things!"}},
	{TutorialState::LIGHT, {"MANAGEMENT", "See that light?  That's a caller trying to connect!"}},
	{TutorialState::CONNECT_1, {"MANAGEMENT", "Try grabbing one of the blue cables and plugging it into the lit port."}},
	{TutorialState::SWITCH_TOP, {"MANAGEMENT", "Great!  Now that you're plugged in, switch the blue switch up."}},
	{TutorialState::CALLER_1, {"CALLER", "Hello?  I need to speak to Doctor Johnson; I broke all of my bones skydiving :("}},
	{TutorialState::RESPONSE_1, {"YOU", "Yes, sir.  Connecting you now."}},
	{TutorialState::LOOKUP_1, {"MANAGEMENT", "You're a natural.  Usually, we would have you look up Doctor Johnson's port yourself."}},
	{TutorialState::LOOKUP_2, {"MANAGEMENT", "However, a recent time crunch has left us without the needed documentation."}},
	{TutorialState::LOOKUP_3, {"MANAGEMENT", "For now, callers will just say the port they want to connect to."}},
	{TutorialState::CONNECT_2, {"MANAGEMENT", "Use the connected red cable to connect to Doctor Johnson on port 23 now."}},
	{TutorialState::SWITCH_BTM, {"MANAGEMENT", "Good job, now switch the red switch to the bottom to ring him."}},
	{TutorialState::RINGING, {"MANAGEMENT", "Great, now wait on the line for him to pick up!"}},
	{TutorialState::RESPONSE_2, {"YOU", "Caller, I am ringing Doctor Johnson now."}},
	{TutorialState::PICKUP_1, {"MANAGEMENT", "See the light turn on?  He is on the line.  Flip the red switch up!"}},
	{TutorialState::PICKUP_2, {"DR JOHNSON", "Hello?  I'm very busy committing insurance fraud!"}},
	{TutorialState::CALLER_2, {"CALLER", "DOCTOR!  It happened again!"}},
	{TutorialState::SWITCH_MID, {"MANAGEMENT", "Wow, spicy.  Flip both switches back to the middle to let the callers undisturbed."}},
	{TutorialState::WAITING_1, {"MANAGEMENT", "Now all that's left to do is wait for them to be done on their call."}},
	{TutorialState::WAITING_2, {"MANAGEMENT", "And wait..."}},
	{TutorialState::WAITING_3, {"MANAGEMENT", "And wait............"}},
	{TutorialState::WAITING_4, {"MANAGEMENT", "So, uh, see any good movies lately?"}},
	{TutorialState::WAITING_5, {"YOU", "Well I-"}},
	{TutorialState::WAITING_6, {"MANAGEMENT", "THANK GOODNESS! I mean er- they've finished talking."}},
	{TutorialState::DISCONNECT, {"MANAGEMENT", "See that the lights turned off?  Just unplug the cords and that's that!"}},
	{TutorialState::FINISH_1, {"MANAGEMENT", "Good job handling your first call!"}},
	{TutorialState::FINISH_2, {"MANAGEMENT", "We are still ramping up operations here at Talkutronix, so your duties are currently limited."}},
	{TutorialState::FINISH_3, {"MANAGEMENT", "Currently, you can only do basic call connections like this."}},
	{TutorialState::FINISH_4, {"MANAGEMENT", "However, we are ramping up fast, so expect more responsibilities in the future!"}},
	{TutorialState::FINISH_5, {"MANAGEMENT", "Anyway, that's the end of your training.  Go ahead and get to it."}},
	{TutorialState::FINISH_6, {"MANAGEMENT", "Oh, and here's a few more call circuits.  Good luck!"}},
	{TutorialState::END, {"DEVELOPER", "HA!  You thought you were going to get to use those!  Only the tutorial is finished.  Go home!"}},
	{TutorialState::GAME_OVER, {"MANAGEMENT", "I had hopes, hopes and dreams.  You just crushed those.  Get out."}}
};
