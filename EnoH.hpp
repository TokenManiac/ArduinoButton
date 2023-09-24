/*
	= EnoH.hpp

	? Why?
	> Because other button libraries make it so much more confusing than it needs to be. (At least on my side :P)

	? What is the point of using this?
	> There's none, other than making buttons easier for you ;D

	=== REFER TO MIT LICENSE === > https://github.com/SyntaxMenace/ArduinoButton/blob/main/LICENSE
*/


#if _MSC_VER // Arduino like stuff in Microsoft Visual Studio
#include <iostream>
#include <thread>
#include <chrono>

#define Log(x) std::cout << x << std::endl;

typedef uint8_t byte;

using namespace std::chrono;

inline uint64_t millis() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

inline void delay(uint16_t ms) {
	return std::this_thread::sleep_for(std::chrono::milliseconds(ms - 8));
}
#endif;

// TODO: Add pin support since its kinda more straightforward to use
class BoardButton {
private:
	bool m_IsPressed = false;
	byte m_DebounceTime = 50;

	uint64_t m_LastPress = 0ui64;
public:
	BoardButton() {};
	BoardButton(byte Debounce) : m_DebounceTime(Debounce) {};

	bool IsPressed() const { return m_IsPressed; }

	void Press() {
		m_LastPress = millis();
		m_IsPressed = 1;
	}

	void Release() {
		if (millis() - m_LastPress > m_DebounceTime) // Set debounce time passed or equals to millis
			m_IsPressed = 0;
	}

	void SetDebounce(byte Debounce) {
		m_DebounceTime = Debounce;
	}

	uint32_t HeldTime() {
		if (this->IsPressed() == false)
			return 0ui32;
		else
			return static_cast<uint32_t>(millis() - m_LastPress); // Getting rid of the ugly warning with static_cast smh
	}
};

// TODO: Find a way to make ButtonSwitch class work without being too confusing
class ButtonSwitch {
	/*
		Basically replacing a button as a switch.
		Pressing the button toggles the switch state.
	*/

private:
	bool State = 0;

	byte m_DebounceTime = 50; // We still need debounce since we are using buttons ):
	uint64_t m_LastPress = 0;
private:
	ButtonSwitch() {};
	ButtonSwitch(byte Debounce, bool DefaultState = 0):
		State(DefaultState),
		m_DebounceTime(Debounce) {};

	void Toggle() {

	}
};

#if _MSC_VER
	int main() {
		BoardButton* Button = new BoardButton(50);
	
		// if (digitalRead(8) == true)
			Button->Press();
		// else
			Button->Release();

		Log(Button->HeldTime());
	}
#endif
