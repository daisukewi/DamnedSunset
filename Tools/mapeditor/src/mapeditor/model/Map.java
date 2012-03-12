/**
 * 
 */
package mapeditor.model;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Set;
import java.util.Vector;

import mapeditor.util.CellType;
import mapeditor.util.ColorEntity;
import mapeditor.util.EntityType;
import mapeditor.util.ExportableData;
import mapeditor.util.Position;

/**
 * @author Guibrush
 *
 */
public class Map implements Serializable, ExportableData {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public static final String ENTITY_NAME = "name";
	
	public static final String ENTITY_TYPE = "type";
	
	public static final String ENTITY_POSITION = "position";
	
	public static final String ENTITY_DIMENSION = "dimension";
	
	public static final String CELL_POSITION = "position";
	
	public static final int MAX_HEIGHT = 100;
	
	public static final int MAX_WIDTH = 100;

	private HashMap<Integer, Entity> _entityList;
	
	private Cell[][] _map;
	
	private int _mapWidth;
	
	private int _mapHeight;
	
	private int _entityID;
	
	private HashMap<String, String> _paramList;
	
	private boolean _importing;
	
	private String _importingCell;
	
	private String _importingEntity;
	
	private HashMap<String, String> _importingEntityParameters;
	
	private Position _importingEntityPosition;
	
	private int _importingMaxX;
	
	private int _importingMaxY;
	
	private String _importingEntityType;
	
	public Map() {
		
		_importing = false;
		
		_importingCell = null;
		
		_importingEntity = null;
		
		_importingEntityParameters = new HashMap<String, String>();
		
		_importingEntityPosition = null;
		
		_importingMaxX = 0;
		
		_importingMaxY = 0;
		
		_importingEntityType = null;
		
		_entityList = new HashMap<Integer, Entity>();
		_entityID = 0;
		
		_paramList = new HashMap<String, String>();
		
		_mapWidth = MAX_WIDTH;
		_mapHeight = MAX_HEIGHT;
		
		_map = new Cell[_mapWidth][_mapHeight];
		for (int x = 0; x < _mapWidth; x++)
			for (int y = 0; y < _mapHeight; y++)
				_map[x][y] = null;
		
	}
	
	public Map(int width, int height, CellType basicCell) {
		
		_importing = false;
		
		_importingCell = null;
		
		_importingEntity = null;
		
		_importingEntityParameters = new HashMap<String, String>();
		
		_importingEntityPosition = null;
		
		_importingMaxX = 0;
		
		_importingMaxY = 0;
		
		_importingEntityType = null;
		
		_entityList = new HashMap<Integer, Entity>();
		_entityID = 0;
		
		_paramList = new HashMap<String, String>();
		
		_mapWidth = width;
		_mapHeight = height;
		
		// Inicializaci�n del mapa con la celda b�sica pasada como par�metro.
		_map = new Cell[_mapWidth][_mapHeight];
		for (int x = 0; x < _mapWidth; x++)
			for (int y = 0; y < _mapHeight; y++)
				_map[x][y] = new Cell(basicCell);
		
	}
	
	private boolean checkPositions(Position[] posList) {
		
		boolean full = false;
		
		int i = 0;
		
		while ((i < posList.length) && (!full)) {
			
			full = _map[posList[i].getX()][posList[i].getY()].getEntity() != 0;
			i++;
			
		}
		
		return !full;
		
	}
	
	private void closeImport() {
		
		// Redimensiono el mapa resultante para ajustarlo a las dimensiones reales del mapa importado.
		_mapWidth = _importingMaxX + 1;
		_mapHeight = _importingMaxY + 1;
		
		Cell[][] tempMap = new Cell[_mapWidth][_mapHeight];
		
		for (int x = 0; x < _mapWidth; x++)
			for (int y = 0; y < _mapHeight; y++)
				tempMap[x][y] = _map[x][y];
		
		_map = tempMap;
		
		_importing = false;
		
	}

	private void closeElement() {
		
		_importingCell = null;
		_importingEntity = null;
		
		// Si tengo par�metros para importar en este punto es porque he cerrado una entidad y ya no hay mas par�metros para leer
		// por lo tanto escribo los par�metros le�dos.
		if (!_importingEntityParameters.isEmpty()) {
			
			for (String name : _importingEntityParameters.keySet())
				newEntityParameter(getEntityID(_importingEntityPosition), name, _importingEntityParameters.get(name));
			
			_importingEntityParameters.clear();
			
			_importingEntityPosition = null;
			
			_importingEntityType = null;
			
		}
		
	}

	private void extractShortEntityParameter(String[] s) {
		
		_importingEntityParameters.put(s[0], s[2].replace(",", ""));
		
		// Actualizo el valor del tipo de entidad para poder construirla.
		if (s[0].equals(ENTITY_TYPE))
			_importingEntityType = s[2].replace("\"", "").replace(",", "");
		
	}

	private void checkBeginElement(Vector<CellType> cells, String[] s) {
		
		int index = cells.indexOf(new CellType(s[0]));
		
		// Si es definici�n de nombre de celda me la guardo para empezar a leer la informaci�n de la celda.
		if (index != -1)
			_importingCell = s[0];
		else {
			
			// Si en este punto leo una apertura de llave despu�s de un nombre es porque lo que viene ahora es una
			// definici�n de entidad y el nombre es el par�metro name de la misma.
			if (s[2].equals("{")) {
				
				_importingEntityParameters.put(ENTITY_NAME, s[0].replace(",", ""));
				
				_importingEntity = s[0];
				
			}
			
		}
		
	}

	private void extractCellParameter(String[] s) {
		
		if (s[0].equals(CELL_POSITION)) {
			
			Position pos = new Position(Integer.valueOf(s[3].replace(",", "")), Integer.valueOf(s[4].replace(",", "")));
			
			_map[pos.getX()][pos.getY()] = new Cell(new CellType(_importingCell));
			
			// Despu�s de actualizar la posici�n actualizo tambi�n el m�ximo valor de x e y acumulado
			// para redimensionar al final el tama�o del mapa.
			if (pos.getX() > _importingMaxX)
				_importingMaxX = pos.getX();
			
			if (pos.getY() > _importingMaxY)
				_importingMaxY = pos.getY();
			
		}
		
	}

	private void extractLongEntityParameter(String[] s) {
		
		String value = "";
		
		for (int j = 2; j < s.length; j++)
			if (j == (s.length - 1))
				value = value + s[j].replace(",", "");
			else
				value = value + s[j] + " ";
		
		_importingEntityParameters.put(s[0], value);
		
		// Actualizo el valor de la posici�n y el tipo de la entidad para poder construirla.
		if (s[0].equals(ENTITY_POSITION))
			_importingEntityPosition = new Position(Integer.valueOf(s[3].replace(",", "")), Integer.valueOf(s[4].replace(",", "")));
		else
			if (s[0].equals(ENTITY_TYPE))
				_importingEntityType = value.replace("\"", "");
		
	}

	private void buildEntity(Vector<ColorEntity> entities) {
		
		int entityIndex = entities.indexOf(new ColorEntity(null, new EntityType(_importingEntityType), 0, 0));
		
		int entityHeight = entities.get(entityIndex).getHeight();
		
		int entityWidth = entities.get(entityIndex).getWidth();
		
		Position[] posList = new Position[entityHeight * entityWidth];
		
		int i = 0;
		
		for (int x = _importingEntityPosition.getX(); x < (_importingEntityPosition.getX() + entityWidth); x++)
			for (int y = _importingEntityPosition.getY(); y < (_importingEntityPosition.getY() + entityHeight); y++) {
				
				posList[i] = new Position(x, y);
				i++;
				
			}
		
		EntityType entityType = (EntityType) entities.get(entities.indexOf(new ColorEntity(null, new EntityType(_importingEntityType), 0, 0))).getType();
		
		newEntity(posList, new Entity(entityType), entityHeight, entityWidth);
		
	}
	
	public boolean newEntity(Position[] posList, Entity entity, int height, int width) {
		
		if (checkPositions(posList)) {
		
			_entityID++;
			
			_entityList.put(_entityID, entity);
			
			_entityList.get(_entityID).newParameter(ENTITY_TYPE, "\"" + entity.getType().getType() + "\"");
			
			_entityList.get(_entityID).newParameter(ENTITY_NAME, "Entity" + _entityID);
			
			_entityList.get(_entityID).newParameter(ENTITY_DIMENSION, "{ " + height + ", " + width + " }");
			
			_entityList.get(_entityID).newParameter(ENTITY_POSITION, "{ " + posList[0].getX() + ", " + posList[0].getY() + " }");
			
			for (int i = 0; i < posList.length; i++) {
				
				_map[posList[i].getX()][posList[i].getY()].setEntity(_entityID);
				_map[posList[i].getX()][posList[i].getY()].setPrimaryEntity(new Position(posList[0].getX(), posList[0].getY()));
				
			}
			
			return true;
		
		}
		else
			return false;
		
	}
	
	public void removeAllEntityParameters(int entityID) {
		
		String type = _entityList.get(entityID).getParameter(ENTITY_TYPE);
		
		String name = _entityList.get(entityID).getParameter(ENTITY_NAME);
		
		String dimension = _entityList.get(entityID).getParameter(ENTITY_DIMENSION);
		
		String position = _entityList.get(entityID).getParameter(ENTITY_POSITION);
		
		_entityList.get(entityID).removeAllParameters();
		
		_entityList.get(entityID).newParameter(ENTITY_TYPE, type);
		
		_entityList.get(entityID).newParameter(ENTITY_NAME, name);
		
		_entityList.get(entityID).newParameter(ENTITY_DIMENSION, dimension);
		
		_entityList.get(entityID).newParameter(ENTITY_POSITION, position);
		
	}
	
	public void newEntityParameter(int entityID, String paramName, String paramValue) {
		
		_entityList.get(entityID).newParameter(paramName, paramValue);
		
	}
	
	public int getEntityID(Position pos) {
		
		return _map[pos.getX()][pos.getY()].getEntity();
		
	}
	
	public Entity getEntity(int entityID) {
		
		return _entityList.get(entityID);
		
	}
	
	public Set<Integer> getAllEntityIDs() {
		
		return _entityList.keySet();
		
	}
	
	public boolean removeEntity(Position[] posList, int entityID) {
		
		for (int i = 0; i < posList.length; i++) {
			
			_map[posList[i].getX()][posList[i].getY()].setEntity(0);
			_map[posList[i].getX()][posList[i].getY()].setPrimaryEntity(null);
			
		}
		
		if (_entityList.remove(entityID) == null)
			return false;
		else
			return true;
		
	}
	
	public Cell getCell(Position pos) {
		
		return _map[pos.getX()][pos.getY()];
		
	}
	
	public void setCellType(Position pos, CellType type) {
		
		_map[pos.getX()][pos.getY()].setType(type);
		
	}
	
	public HashMap<String, String> getParameters() {
		
		return _paramList;
		
	}
	
	public void setParameters(HashMap<String, String> parameters) {
		
		_paramList = parameters;
		
	}
	
	public int getMapWidth() {
		
		return _mapWidth;
		
	}
	
	public int getMapHeight() {
		
		return _mapHeight;
		
	}
/*
	@Override
	public void exportData(int type) {
		
		notifyDataToExport("Map = {\n\n");
		
		for (int x = 0; x < _mapWidth; x++)
			for (int y = 0; y < _mapHeight; y++) {
				
				String s1 = "";
				
				s1 = s1 + "\t" + _map[x][y].getType().getType() + " = {\n";
				
				s1 = s1 + "\t\t" + CELL_POSITION + " = { " + x + ", " + y + " },\n";
				
				s1 = s1 + "\t}\n\n";
				
				notifyDataToExport(s1);
				
			}
		
		for (int entityID : _entityList.keySet()) {
			
			Entity entity = _entityList.get(entityID);
			
			String s2 = "";
			
			s2 = s2 + "\t" + entity.getParameter(ENTITY_NAME) + " = {\n";
			
			for (String name : entity.getParamNames()) {
				
				if (!name.equals(ENTITY_DIMENSION) && !name.equals(ENTITY_NAME))
					s2 = s2 + "\t\t" + name + " = " + entity.getParameter(name) + ",\n";
				
			}
			
			s2 = s2 + "\t}\n\n";
			
			notifyDataToExport(s2);
			
		}
		
		notifyDataToExport("}\n\n");
		
		notifyFinishExport();

	}
*/
	@Override
	public String getGridAttributes() {
		
		String s = "\tGrid = {\n";
		
		for (String name : _paramList.keySet())
			s = s + "\t\t" + name + " = " + _paramList.get(name) + ",\n";
		
		s = s + "\t\twidth = " + _mapWidth + ",\n";
		s = s + "\t\theight = " + _mapHeight + ",\n";
		
		s = s + "\t},\n\n";
		
		return s;
	}
	
	@Override
	public String getAllEntitiesAttributes() {
		
		String s = "";
		
		for (int entityID : _entityList.keySet()) {
			
			Entity entity = _entityList.get(entityID);
			
			s = s + "\t" + entity.getParameter(ENTITY_NAME) + " = {\n";
			
			for (String name : entity.getParamNames()) {
				
				if (!name.equals(ENTITY_DIMENSION) && !name.equals(ENTITY_NAME))
					s = s + "\t\t" + name + " = " + entity.getParameter(name) + ",\n";
				
			}
			
			s = s + "\t},\n\n";
			
		}
		
		return s;
	}
	
	@Override
	public String getCellAttributes(CellType cell) {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public void importData(String data, int type, Vector<CellType> cells, Vector<ColorEntity> entities) {
		
		// Compruebo el tipo que me han pasado para importar los datos correctos.
		if (type == 0) {
			
			// Compruebo si estoy importando o estoy al principio de la secci�n del archivo que me importa.
			if ((data.contains("Map")) || _importing) {
				
				// Si antes de hacer nada me encuentro con un cierre de llave dejo de importar y ajusto el mapa.
				if (data.startsWith("}"))
					closeImport();
				else
					_importing = true;
				
				// Compruebo que no estoy al principio y voy a leer datos v�lidos.
				if (!data.contains("Map")) {
					
					// Quito todos los tabuladores y parto la cadena para quedarme con las partes que me importan.
					data = data.replace("\t", "");
					String[] s = data.split(" ");
					
					// Si me encuentro con un cierre de llave en esta altura es porque se cierra una secci�n de celda o de entidad.
					if (data.startsWith("}"))
						closeElement();
					
					// Miro si la cadena le�da es de longitud 3 porque podr�a ser una definici�n de nombre de celda o entidad
					// o una definici�n de par�metro de entidad.
					if ((s != null) && (s.length == 3)) {
						
						checkBeginElement(cells, s);
						
						// Si estoy leyendo una entidad y no hay apertura de llave en este punto es porque lo que estoy leyendo es
						// un par�metro de la entidad actual. Me la guardo, pues.
						if ((_importingEntity != null) && (!s[2].equals("{")))
							extractShortEntityParameter(s);
						
					}
					else
						// Si la longitud de la cadena le�da es mayor que 6 es porque estoy leyendo un par�metro de entidad o de celda.
						if ((s != null) && (s.length > 3))
							// Si estoy leyendo una celda actualizo el informaci�n de la misma.
							if (_importingCell != null)
								extractCellParameter(s);
							else
								// Si estoy leyendo una entidad me guardo el par�metro.
								if (_importingEntity != null)
									extractLongEntityParameter(s);
					
					// Miro a ver si tengo todo lo necesario para construir la entidad y la construyo.
					if ((_importingEntityType != null) && (_importingEntityPosition != null))
						buildEntity(entities);
					
				}
				
			}
			
		}
		
	}

}
