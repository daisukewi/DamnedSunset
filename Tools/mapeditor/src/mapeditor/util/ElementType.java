/**
 * 
 */
package mapeditor.util;

import java.io.Serializable;

/**
 * @author Guibrush
 *
 */
public class ElementType implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private String _type;
	
	public ElementType(String type) {
		
		_type = type;
		
	}

	/**
	 * @return the type
	 */
	public String getType() {
		return _type;
	}

	/**
	 * @param type the type to set
	 */
	public void setType(String type) {
		this._type = type;
	}
	
	public boolean equals(Object obj) {
		
		if (obj == null)
			return false;
		else
			if (obj instanceof ElementType) {
				if (((ElementType) obj).getType().equals(_type))
					return true;
				else
					return false;
			}
			else
				return false;
		
	}

}
