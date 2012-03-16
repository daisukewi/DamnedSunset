/**
 * 
 */
package mapeditor.model;

import java.awt.Color;
import java.io.Serializable;
import java.util.Set;
import java.util.Vector;

import mapeditor.util.CellType;
import mapeditor.util.ColorCell;
import mapeditor.util.ColorEntity;
import mapeditor.util.EntityType;
import mapeditor.util.ExportableData;

/**
 * @author Guibrush
 *
 */
public class Preferences implements Serializable, ExportableData {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private Vector<ColorCell> _cellTypes;
	
	private Vector<ColorEntity> _entityTypes;
	
	private boolean _importing;
	
	private String _importingCell;
	
	public Preferences() {
		
		_cellTypes = new Vector<ColorCell>();
		_entityTypes = new Vector<ColorEntity>();
		
		_importing = true;
		
		_importingCell = null;
		
	}
	
	public boolean newCellType(ColorCell cellType) {
		
		if (_cellTypes.contains(cellType))
			return false;
		else {
			
			_cellTypes.add(cellType);
			return true;
			
		}
		
	}
	
	public boolean newEntityType(ColorEntity entityType) {
		
		if (_entityTypes.contains(entityType))
			return false;
		else {
			
			_entityTypes.add(entityType);
			return true;
			
		}
		
	}
	
	public Color getColorTypeCell(CellType cellType) {
		
		return _cellTypes.get(_cellTypes.indexOf(new ColorCell(null, cellType))).getColor();
		
	}
	
	public Color getColorTypeEntity(EntityType entityType) {
		
		return _entityTypes.get(_entityTypes.indexOf(new ColorEntity(null, entityType, 0, 0))).getColor();
		
	}
	
	public int getEntityHeight(EntityType entityType) {
		
		return _entityTypes.get(_entityTypes.indexOf(new ColorEntity(null, entityType, 0, 0))).getHeight();
		
	}
	
	public int getEntityWidth(EntityType entityType) {
		
		return _entityTypes.get(_entityTypes.indexOf(new ColorEntity(null, entityType, 0, 0))).getWidth();
		
	}
	
	public String getCellParameter(CellType cellType, String paramName) {
		
		return _cellTypes.get(_cellTypes.indexOf(new ColorCell(null, cellType))).getParameter(paramName);
		
	}
	
	public void newCellParameter(CellType cellType, String paramName, String paramValue) {
		
		_cellTypes.get(_cellTypes.indexOf(new ColorCell(null, cellType))).newParameter(paramName, paramValue);
		
	}
	
	public void removeCellParameter(CellType cellType, String paramName) {
		
		_cellTypes.get(_cellTypes.indexOf(new ColorCell(null, cellType))).removeParameter(paramName);
		
	}
	
	public void removeAllCellParameters(CellType cellType) {
		
		_cellTypes.get(_cellTypes.indexOf(new ColorCell(null, cellType))).removeAllParameters();
		
	}
	
	public Set<String> getCellParamNames(CellType cellType) {
		
		return _cellTypes.get(_cellTypes.indexOf(new ColorCell(null, cellType))).getParamNames();
		
	}
	
	public Vector<CellType> getCellTypes() {
		
		Vector<CellType> tempVector = new Vector<CellType>();
		
		for (ColorCell colorCell : _cellTypes)
			tempVector.add((CellType) colorCell.getType());
		
		return tempVector;
		
	}
	
	public Vector<EntityType> getEntityTypes() {
		
		Vector<EntityType> tempVector = new Vector<EntityType>();
		
		for (ColorEntity colorEntity : _entityTypes)
			tempVector.add((EntityType) colorEntity.getType());
		
		return tempVector;
		
	}
	
	public Vector<ColorEntity> getColorEntities() {
		
		return _entityTypes;
		
	}

	@Override
	public String getGridAttributes() {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public String getAllEntitiesAttributes() {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public String getCellAttributes(CellType cell) {
		
		String s = "";
		
		for (String name : _cellTypes.get(_cellTypes.indexOf(new ColorCell(null, cell))).getParamNames())
			s = s + "\t\t" + name + " = " + _cellTypes.get(_cellTypes.indexOf(new ColorCell(null, cell))).getParameter(name) + ",\n";
		
		return s;
	}
	
	@Override
	public void importData(String data, int type, Vector<CellType> cells, Vector<ColorEntity> entities) {
		
		// Compruebo el tipo que me han pasado para importar los datos correctos.
		if (type == 0) {
			
			// Compruebo si estoy importando o al principio de la sección del archivo que me importa.
			if (data.contains("Grid") || _importing) {
				
				// Si antes de hacer nada me encuentro con un cierre de llave activo el flag para dejar de importar.
				if (data.startsWith("}"))
					_importing = false;
				else
					_importing = true;
				
				// Compruebo que no estoy al principio para leer datos válidos
				if (!data.contains("Grid")) {
					
					// Quito todos los tabuladores y parto la cadena para quedarme con las partes que me importan.
					data = data.replace("\t", "");
					String[] s = data.split(" ");
					
					// Si me encuentro con un cierre de llave en esta altura es porque se cierra una sección de celda.
					if (data.startsWith("}"))
						_importingCell = null;
					
					// Comruebo si estoy en leyendo el principio de una sección de celda y miro si la celda existe
					// para apuntarla y empezar a leer la información de la misma.
					if ((s != null) && (s.length >= 3) && (s[2] != null) && (s[2].equals("{"))) {
						
						int index = _cellTypes.indexOf(new ColorCell(null, new CellType(s[0])));
						
						if (index != -1)
							_importingCell = s[0];
						
					}
					else
						// Si no estoy al principio de una sección de celda y estoy leyendo una celda es porque lo que viene ahora es un parámetro
						// de la misma, por tanto me lo guardo.
						if (_importingCell != null)
							_cellTypes.get(_cellTypes.indexOf(new ColorCell(null, new CellType(_importingCell)))).newParameter(s[0], s[2].replace(",", ""));
					
				}
				
			}
			
		}
		
	}

}
