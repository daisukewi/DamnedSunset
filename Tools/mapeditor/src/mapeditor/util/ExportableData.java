/**
 * 
 */
package mapeditor.util;

import java.util.Vector;

/**
 * @author Guibrush
 *
 */
public interface ExportableData {
	
	public String getGridAttributes();
	
	public String getAllEntitiesAttributes();
	
	public String getCellAttributes(CellType cell);
	
	public void importData(String data, int type, Vector<CellType> cells, Vector<ColorEntity> entities);

}
