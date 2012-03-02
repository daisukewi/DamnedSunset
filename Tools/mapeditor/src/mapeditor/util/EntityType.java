/**
 * 
 */
package mapeditor.util;

/**
 * @author Guibrush
 *
 */
public class EntityType extends ElementType {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public EntityType(String type) {
		
		super(type);
		
	}
	
	public boolean equals(Object obj) {
		
		if (obj == null)
			return false;
		else
			if (obj instanceof EntityType) {
				if (((EntityType) obj).getType().equals(super.getType()))
					return true;
				else
					return false;
			}
			else
				return false;
		
	}

}
