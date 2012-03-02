/**
 * 
 */
package mapeditor.view;

import javax.swing.JButton;

import mapeditor.util.ElementType;

/**
 * @author Guibrush
 *
 */
public class TypeButtonGroup {
	
	private ElementType _type;
	
	private JButton _button;
	
	public TypeButtonGroup(ElementType type, JButton button) {
		
		_type = type;
		_button = button;
		
	}

	/**
	 * @return the type
	 */
	public ElementType getType() {
		return _type;
	}

	/**
	 * @return the button
	 */
	public JButton getButton() {
		return _button;
	}

	/**
	 * @param type the type to set
	 */
	public void setType(ElementType type) {
		this._type = type;
	}

	/**
	 * @param button the button to set
	 */
	public void setButton(JButton button) {
		this._button = button;
	}
	
	public boolean equals(Object obj) {
		
		if (obj == null)
			return false;
		else
			if (obj instanceof TypeButtonGroup) {
				if (((TypeButtonGroup) obj).getType().equals(_type))
					return true;
				else
					return false;
			}
			else
				return false;
		
	}

}
