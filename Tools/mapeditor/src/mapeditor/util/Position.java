/**
 * 
 */
package mapeditor.util;

import java.io.Serializable;

/**
 * @author Guibrush
 *
 */
public class Position implements Serializable {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private int _x;
	private int _y;
	
	public Position(int x, int y) {
		
		_x = x;
		_y = y;
		
	}

	/**
	 * @return the _x
	 */
	public int getX() {
		return _x;
	}

	/**
	 * @return the _y
	 */
	public int getY() {
		return _y;
	}

	/**
	 * @param x the x to set
	 */
	public void setX(int x) {
		_x = x;
	}

	/**
	 * @param _y the _y to set
	 */
	public void setY(int y) {
		_y = y;
	}

}
