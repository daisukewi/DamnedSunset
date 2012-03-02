/**
 * 
 */
package mapeditor.util;

/**
 * @author Guibrush
 *
 */
public class CellType extends ElementType {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public CellType(String type) {
		
		super(type);
		
	}
	
	public boolean equals(Object obj) {
		
		if (obj == null)
			return false;
		else
			if (obj instanceof CellType) {
				if (((CellType) obj).getType().equals(super.getType()))
					return true;
				else
					return false;
			}
			else
				return false;
		
	}

}
