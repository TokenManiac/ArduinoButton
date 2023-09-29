/*
	= EnoH.hpp

	? Why?
	> Because yes!!!

	? What is the point of using this?
	> There's none, other than making buttons easier for you ;D

	=== REFER TO MIT LICENSE === > https://github.com/SyntaxMenace/ArduinoButton/blob/main/LICENSE
*/

class BoardButton {
private:
	byte Pin = 0;

	byte m_DebounceTime = 50;

	mutable bool m_IsPressed = false;
	mutable uint64_t m_LastPress = 0ui64;
public:
	BoardButton(byte pin) : Pin(pin) {}
	BoardButton(byte pin, byte Debounce) : Pin(pin), m_DebounceTime(Debounce) {}

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

	void SetDebounce(byte Debounce) {
		m_DebounceTime = Debounce;
	}

	uint64_t HeldTime() const {
		if (this->IsPressed() == false) {
			return 0ui32;
		} else {
			return static_cast<uint64_t>(millis() - m_LastPress);
		}
	}
};
