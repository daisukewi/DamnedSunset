/**
 * 
 */
package mapeditor.util;

import java.awt.Color;

/**
 * @author Guibrush
 *
 */
public class ColorEntity extends ColorElement {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private int _height, _width;
	
	public ColorEntity(Color color, EntityType type, int height, int width) {
		
		super(color, type);
		
		_height = height;
		_width = width;
	}
	
	/**
	 * @return the height
	 */
	public int getHeight() {
		return _height;
	}

	/**
	 * @return the width
	 */
	public int getWidth() {
		return _width;
	}

	/**
	 * @param height the height to set
	 */
	public void setHeight(int height) {
		this._height = height;
	}

	/**
	 * @param _width the _width to set
	 */
	public void setWidth(int width) {
		this._width = width;
	}

	public boolean equals(Object obj) {
		
		if (obj == null)
			return false;
		else
			if (obj instanceof ColorEntity) {
				if (((ColorEntity) obj).getType().equals(super.getType()))
					return true;
				else
					return false;
			}
			else
				return false;
		
	}

}
