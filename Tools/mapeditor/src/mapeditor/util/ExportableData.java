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
	
	public void exportData(int type);
	
	public void importData(String data, int type, Vector<CellType> cells, Vector<ColorEntity> entities);

}
