/**
 * 
 */
package mapeditor.controler;

import java.awt.Color;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Set;
import java.util.Vector;

import mapeditor.model.Entity;
import mapeditor.model.Map;
import mapeditor.model.Preferences;
import mapeditor.util.CellType;
import mapeditor.util.ColorCell;
import mapeditor.util.ColorEntity;
import mapeditor.util.ControllerListener;
import mapeditor.util.ElementType;
import mapeditor.util.EntityType;
import mapeditor.util.Position;

/**
 * @author Guibrush
 *
 */
public class System {
	
	private Position _posSelected;
	
	private Map _map;
	
	private List<ControllerListener> _listeners;
	
	private FileHandler _fileHandler;
	
	private Preferences _preferences;
	
	private boolean _painting;
	
	private ElementType _elementSelected;
	
	public System() {
		
		_elementSelected = null;
		_painting = false;
		_map = null;
		_posSelected = null;
		_preferences = null;
		_listeners = new ArrayList<ControllerListener>();
		_fileHandler = new FileHandler();
		
	}
	
	private void notifyCellSelected() {
		
		for (ControllerListener listener : _listeners) {
			listener.cellSelected(_posSelected);
		}
		
	}
	
	private void notifyShowCellType() {
		
		for (ControllerListener listener : _listeners) {
			listener.showCellType(_map.getCell(_posSelected).getType().getType());
		}
		
	}
	
	private void notifyShowEntityMessage() {
		
		String message;
		
		if (_map.getCell(_posSelected).getEntity() > 0)
			message = "Información de la entidad:";
		else
			message = "Casilla sin entidad";
		
		for (ControllerListener listener : _listeners) {
			listener.showEntityMessage(message);
		}
		
	}
	
	private void notifyShowEntityParameter(String name, String value) {
		
		for (ControllerListener listener : _listeners) {
			listener.showEntityParameter(name, value);
		}
		
	}
	
	private void notifyCellChanged(Position pos, CellType cellType) {
		
		for (ControllerListener listener : _listeners) {
			listener.cellChanged(pos, cellType);
		}
		
	}
	
	private void notifyNewMap(int width, int height) {
		
		for (ControllerListener listener : _listeners) {
			listener.newMap(width, height);
		}
		
	}
	
	private void notifyCellDeSelected() {
		
		for (ControllerListener listener : _listeners) {
			listener.cellDeSelected();
		}
		
	}
	
	private void notifyPreferencesChanged() {
		
		for (ControllerListener listener : _listeners) {
			listener.preferencesChanged();
		}
		
	}
	
	private void notifyTypeElementSelected(ElementType elementType, int height, int width) {
		
		for (ControllerListener listener : _listeners) {
			listener.typeElementSelected(elementType, height, width);
		}
		
	}
	
	private void notifyTypeElementDeSelected() {
		
		for (ControllerListener listener : _listeners) {
			listener.typeElementDeSelected();
		}
		
	}
	
	private void notifyNewEntity(Position[] posList, EntityType entityType) {
		
		for (ControllerListener listener : _listeners) {
			listener.newEntity(posList, entityType);
		}
		
	}
	
	private void notifyRemoveEntity(Position[] posList) {
		
		for (ControllerListener listener : _listeners) {
			listener.removeEntity(posList);
		}
		
	}
	
	private void notifyAllSelectChanges() {
		
		notifyCellSelected();
		notifyShowCellType();
		notifyShowEntityMessage();
		
		if (_map.getCell(_posSelected).getEntity() > 0) {
			
			Entity entity = _map.getEntity(_map.getEntityID(_posSelected));
			
			Set<String> paramNames = entity.getParamNames();
			
			for (String name : paramNames) {
				
				notifyShowEntityParameter(name, entity.getParameter(name));
				
			}
			
		}
		
	}
	
	private void notifyNewMapLoaded() {
		
		notifyCellDeSelected();
		notifyNewMap(_map.getMapWidth(), _map.getMapHeight());
		
		_posSelected = null;
		
		Position pos = null;
		
		for (int x = 0; x < _map.getMapWidth(); x++)
			for (int y = 0; y < _map.getMapHeight(); y++) {
				
				pos = new Position(x, y);
				notifyCellChanged(pos, _map.getCell(pos).getType());
				
				int entityID = _map.getCell(pos).getEntity();
				
				if (entityID != 0) {
					
					Position entityPos = _map.getCell(pos).getPrimaryEntity();
					
					EntityType entityType = _map.getEntity(entityID).getType();
					
					Position[] posList = new Position[_preferences.getEntityHeight(entityType) * _preferences.getEntityWidth(entityType)];
					
					int i = 0;
					
					for (int xEntity = entityPos.getX(); xEntity < (entityPos.getX() + _preferences.getEntityWidth(entityType)); xEntity++)
						for (int yEntity = entityPos.getY(); yEntity < (entityPos.getY() + _preferences.getEntityHeight(entityType)); yEntity++) {
							
							posList[i] = new Position(xEntity, yEntity);
							i++;
							
						}
					
					notifyNewEntity(posList, entityType);
					
				}
				
			}
		
	}
	
	private void changeCellType(CellType newType) {
		
		_map.setCellType(_posSelected, newType);
		
		notifyAllSelectChanges();
		notifyCellChanged(_posSelected, newType);
		
	}
	
	private void newEntity(EntityType newType) {
		
		Position [] posList = new Position[_preferences.getEntityHeight(newType) * _preferences.getEntityWidth(newType)];
		
		int i = 0;
		
		for (int x = _posSelected.getX() ; x < (_posSelected.getX() + _preferences.getEntityWidth(newType)); x++)
			for (int y = _posSelected.getY(); y < (_posSelected.getY() + _preferences.getEntityHeight(newType)); y++) {
				
				posList[i] = new Position(x, y);
				
				i++;
			}
		
		if (_map.newEntity(posList, new Entity(newType), _preferences.getEntityHeight(newType), _preferences.getEntityWidth(newType))) {
		
			notifyAllSelectChanges();
			notifyNewEntity(posList, newType);
		
		}
		
	}
	
	public void removeEntity() {
		
		Position entityPosition = _map.getCell(_posSelected).getPrimaryEntity();
		
		int entityID = _map.getEntityID(entityPosition);
		
		EntityType entity = _map.getEntity(entityID).getType();
		
		Position [] posList = new Position[_preferences.getEntityHeight(entity) * _preferences.getEntityWidth(entity)];
		
		int i = 0;
		
		for (int x = entityPosition.getX() ; x < (entityPosition.getX() + _preferences.getEntityWidth(entity)); x++)
			for (int y = entityPosition.getY(); y < (entityPosition.getY() + _preferences.getEntityHeight(entity)); y++) {
				
				posList[i] = new Position(x, y);
				
				i++;
			}
		
		if (_map.removeEntity(posList, entityID)) {
			
			notifyRemoveEntity(posList);
			notifyCellDeSelected();
			
		}
		
	}
	
	public void addListener(ControllerListener listener) {
		
		_listeners.add(listener);
		
	}
	
	public void removeAllListeners() {
		
		_listeners.clear();
		
	}
	
	public void newMap(int width, int height, CellType basicCell) {
		
		_map = new Map(width, height, basicCell);
		
	}
	
	public void clicked(Position pos) {
		
		notifyCellDeSelected();
		
		_posSelected = pos;
		
		if (!_painting) {
			
			notifyAllSelectChanges();
		}
		else {
			if (_elementSelected instanceof CellType)
				changeCellType((CellType) _elementSelected);
			else
				if (_elementSelected instanceof EntityType)
					newEntity((EntityType) _elementSelected);
		}
	}
	
	public void clicked(ElementType type) {
		
		_painting = true;
		
		_elementSelected = type;
		
		_posSelected = null;
		
		notifyCellDeSelected();
		
		if (type instanceof EntityType)
			notifyTypeElementSelected(type, _preferences.getEntityHeight((EntityType) type), _preferences.getEntityWidth((EntityType) type));
		else
			notifyTypeElementSelected(type, 0, 0);
		
	}
	
	public void clickedSecond() {
		
		_painting = false;
		
		_elementSelected = null;
		
		_posSelected = null;
		
		notifyCellDeSelected();
		
		notifyTypeElementDeSelected();
		
	}
	
	public boolean initialized() {
		
		return _map != null; 
		
	}
	
	public void initializePreferences() {
		
		_preferences = new Preferences();
		
	}
	
	public boolean newCellType(Color color, String cellType) {
		
		boolean inserted = _preferences.newCellType(new ColorCell(color, new CellType(cellType)));
		
		if (inserted)
			notifyPreferencesChanged();
		
		return inserted;
		
	}
	
	public boolean newEntityType(Color color, String entityType, int height, int width) {
		
		boolean inserted = _preferences.newEntityType(new ColorEntity(color, new EntityType(entityType), height, width));
		
		if (inserted)
			notifyPreferencesChanged();
		
		return inserted;
		
	}
	
	public HashMap<String, String> getEntityParameters() {
		
		HashMap<String, String> parameters = new HashMap<String, String>();
		
		for (String name : _map.getEntity(_map.getEntityID(_posSelected)).getParamNames()) {
			
			if ((!name.equals(Map.ENTITY_TYPE)) && (!name.equals(Map.ENTITY_DIMENSION)) && (!name.equals(Map.ENTITY_POSITION)))
				parameters.put(name, _map.getEntity(_map.getEntityID(_posSelected)).getParameter(name));
			
		}
		
		return parameters;
		
	}
	
	public void setEntityParameters(HashMap<String, String> parameters) {
		
		int entityID = _map.getEntityID(_posSelected);
		
		_map.removeAllEntityParameters(entityID);
		
		if (!parameters.isEmpty())
			for (String name : parameters.keySet()) {
				
				_map.newEntityParameter(entityID, name, parameters.get(name));
				
			}
		
	}
	
	public HashMap<String, String> getCellParameters() {
		
		HashMap<String, String> parameters = new HashMap<String, String>();
		
		for (String name : _preferences.getCellParamNames((CellType) _elementSelected)) {
			
			parameters.put(name, _preferences.getCellParameter((CellType) _elementSelected, name));
			
		}
		
		return parameters;
		
	}
	
	public void setCellParameters(HashMap<String, String> parameters) {
		
		_preferences.removeAllCellParameters((CellType) _elementSelected);
		
		if (!parameters.isEmpty())
			for (String name : parameters.keySet()) {
				
				_preferences.newCellParameter((CellType) _elementSelected, name, parameters.get(name));
				
			}
		
	}
	
	public Color getPreferencesColorTypeCell(CellType cellType) {
		
		return _preferences.getColorTypeCell(cellType);
		
	}
	
	public Color getPreferencesColorTypeEntity(EntityType entityType) {
		
		return _preferences.getColorTypeEntity(entityType);
		
	}
	
	public Vector<CellType> getPreferencesCellTypes() {
		
		return _preferences.getCellTypes();
		
	}
	
	public String[] getPreferencesStringCellTypes() {
		
		Vector<CellType> tempVector = getPreferencesCellTypes();
		
		String[] temp = new String[tempVector.size()];
		
		for (int i = 0; i < temp.length; i++)
			temp[i] = tempVector.get(i).getType();
		
		return temp;
		
	}
	
	public Vector<EntityType> getPreferencesEntityTypes() {
		
		return _preferences.getEntityTypes();
		
	}
	
	public HashMap<String, String> getMapParameters() {
		
		return _map.getParameters();
		
	}
	
	public void setMapParameters(HashMap<String, String> parameters) {
		
		_map.setParameters(parameters);
		
	}
	
	public void saveMap(File file) {
		
		if (_map != null)
			try {
				file.createNewFile();
				if (file.canWrite())
					_fileHandler.saveData(file, _map);
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		
	}
	
	public void loadMap(File file) {
		
		if (file.exists() && file.canRead()) {
			_map = (Map) _fileHandler.openData(file);
		
			notifyNewMapLoaded();
			
		}
		
	}
	
	public void savePreferences(File file) {
		
		if (_preferences != null) {
			try {
				file.createNewFile();
				if (file.canWrite())
					_fileHandler.saveData(file, _preferences);
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}
	
	public void openPreferences(File file) {
		
		if (file.exists() && file.canRead())
			_preferences = (Preferences) _fileHandler.openData(file);
		
	}
	
	public void exportMap(File file) {
		
		if (_map != null)
			try {
				file.createNewFile();
				if (file.canWrite()) {
					
					_fileHandler.initExportData(file);
					
					_fileHandler.exportData("Map = {\n\n");
					
					_fileHandler.exportData(_preferences.getGridAttributes());
					
					_fileHandler.exportData(_map.getGridAttributes());
					
					/*int width = _map.getMapWidth();
					int height = _map.getMapHeight();
					String s = "";
					
					for (int x = 0; x < width; x++)
						for (int y = 0; y < height; y++) {
							
							CellType cell = _map.getCell(new Position(x, y)).getType();
							s = "\t" + cell.getType() + x + "_" + y + " = {\n";
							s = s + "\t\ttype = \"" + cell.getType() + "\",\n";
							s = s + "\t\t" + Map.CELL_POSITION + " = { " + x + ", " + y + " },\n";
							s = s + _preferences.getCellAttributes(cell);
							s = s + "\t},\n\n";
							_fileHandler.exportData(s);
							
						}*/
					
					
					_fileHandler.exportData(_map.getAllEntitiesAttributes());
					
					_fileHandler.exportData("}");
					
					_fileHandler.closeExportFile();
					
				}
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		
	}
	
	public void exportHeightmapImage(File file)
	{
		if (_map != null)
		{
			HeightMapExporter hm = new HeightMapExporter(_map.getMapWidth(), _map.getMapHeight(), _preferences);
			hm.ProcessMap(_map);
			hm.SaveImageHeightmap(file);
		}
	}
	
	public void importMap(File file) {
		
		if (file.exists() && file.canRead()) {
			
			_fileHandler.initImportData(file);
			
			_map = new Map();
			
			String line = _fileHandler.importData();
			
			while (line != null) {
				
				_preferences.importData(line, 0, null, null);
				_map.importData(line, 0, _preferences.getCellTypes(), _preferences.getColorEntities());
				line = _fileHandler.importData();
				
			}
			
			_fileHandler.closeImportFile();
			
			notifyNewMapLoaded();
			
		}
		
	}

}
