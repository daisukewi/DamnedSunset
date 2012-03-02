/**
 * 
 */
package mapeditor.util;

import java.awt.Color;
import java.io.Serializable;

/**
 * @author Guibrush
 *
 */
public class ColorElement implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private Color _color;
	
	private ElementType _type;
	
	public ColorElement(Color color, ElementType type) {
		
		_color = color;
		_type = type;
		
	}

	/**
	 * @return the color
	 */
	public Color getColor() {
		return _color;
	}

	/**
	 * @return the type
	 */
	public ElementType getType() {
		return _type;
	}

	/**
	 * @param color the color to set
	 */
	public void setColor(Color color) {
		this._color = color;
	}

	/**
	 * @param type the type to set
	 */
	public void setType(ElementType type) {
		this._type = type;
	}
	
	public boolean equals(Object obj) {
		
		if (obj == null)
			return false;
		else
			if (obj instanceof ColorElement) {
				if (((ColorElement) obj).getType().equals(_type))
					return true;
				else
					return false;
			}
			else
				return false;
		
	}

}
