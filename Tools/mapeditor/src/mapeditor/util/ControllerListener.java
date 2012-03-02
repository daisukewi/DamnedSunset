/**
 * 
 */
package mapeditor.util;


/**
 * @author Guibrush
 *
 */
public interface ControllerListener {
	
	public void cellSelected(Position cell);
	
	public void cellDeSelected();
	
	public void cellChanged(Position cell, CellType celltype);
	
	public void newMap(int width, int height);
	
	public void showCellType(String cellType);
	
	public void showEntityMessage(String message);
	
	public void showEntityParameter(String name, String value);
	
	public void preferencesChanged();
	
	public void typeElementSelected(ElementType elementType, int height, int width);
	
	public void typeElementDeSelected();
	
	public void newEntity(Position[] posList, EntityType entityType);
	
	public void removeEntity(Position[] posList);

}
