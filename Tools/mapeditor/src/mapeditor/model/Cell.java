/**
 * 
 */
package mapeditor.model;

import java.io.Serializable;

import mapeditor.util.CellType;
import mapeditor.util.Position;

/**
 * @author Guibrush
 *
 */

public class Cell implements Serializable {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private CellType _type;
	
	private int _entity;
	
	private Position _primaryEntity;
	
	public Cell(CellType type) {
		
		_type = type;
		_entity = 0;
		_primaryEntity = null;
				
	}
	
	/**
	 * @return the _type
	 */
	public CellType getType() {
		
		return _type;
		
	}
	
	/**
	 * @return the _entity
	 */
	public int getEntity() {
		
		return _entity;
		
	}
	
	/**
	 * @return the _primaryEntity
	 */
	public Position getPrimaryEntity() {
		
		return _primaryEntity;
		
	}

	/**
	 * @param type the type to set
	 */
	public void setType(CellType type) {
		
		_type = type;
		
	}
	
	/**
	 * @param entity the entity to set
	 */
	public void setEntity(int entity) {
		
		_entity = entity;
		
	}
	
	/**
	 * @param pos the primaryEntity to set
	 */
	public void setPrimaryEntity(Position pos) {
		
		_primaryEntity = pos;
		
	}

}
