/*
	= EnoH.hpp

	Q> What does this do?
	A> This C++ file makes buttons easier to handle in your program, therefore easier to read.

	=== REFER TO MIT LICENSE === > https://github.com/SyntaxMenace/ArduinoButton/blob/main/LICENSE
*/

class BoardButton {
private:
	byte Pin = 0;

	uint16_t m_DebounceTime = 50;

	mutable bool m_IsPressed = false;
	mutable uint64_t m_LastPress = 0ui64;
public:
	BoardButton(byte pin) : Pin(pin) {}
	BoardButton(byte pin, uint16_t Debounce) : Pin(pin), m_DebounceTime(Debounce) {}

	bool IsPressed() const {
		const bool ButtonState = digitalRead(Pin);

		if (millis() - m_LastPress >= m_DebounceTime) {
			m_LastPress = ButtonState && !m_IsPressed ? millis() : m_LastPress;
			m_IsPressed = ButtonState;
			return ButtonState;
		}

		m_LastPress = ButtonState && !m_IsPressed ? millis() : m_LastPress;

		return m_IsPressed;
	}

	uint64_t HeldTime() const {
		if (this->IsPressed() == false) {
			return 0ui32;
		} else {
			return static_cast<uint64_t>(millis() - m_LastPress);
		}
	}

	void SetDebounce(uint16_t Debounce) {
		m_DebounceTime = Debounce;
	}
};

class ButtonSwitch {
private:
	bool SwitchState = 0;

	uint16_t m_Debounce;
	uint64_t m_LastPress = 0;
public:
	ButtonSwitch(uint16_t Debounce) :
		m_Debounce(Debounce) {}
	ButtonSwitch(uint16_t Debounce, bool DefaultState) :
		m_Debounce(DefaultState),
		SwitchState(DefaultState) {}

	bool GetState() const {
		return SwitchState;
	}

	void Toggle() {
		if (millis() - m_LastPress >= m_Debounce) {
			m_LastPress = millis();
			SwitchState = !SwitchState;
		}
	}

	uint32_t Time() const { // returns how many milliseconds passed since last toggle
		return static_cast<uint32_t>(millis() - m_LastPress);
	}
};
