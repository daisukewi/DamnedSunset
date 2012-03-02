/**
 * 
 */
package mapeditor.model;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Set;

import mapeditor.util.EntityType;

/**
 * @author Guibrush
 *
 */
public class Entity implements Serializable {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private EntityType _type;
	
	private HashMap<String, String> _paramList;
	
	public Entity(EntityType type) {
		
		_type = type;
		_paramList = new HashMap<String, String>();
		
	}
	
	public EntityType getType() {
		
		return _type;
		
	}
	
	public void setType(EntityType type) {
		
		_type = type;
		
	}
	
	public String getParameter(String name) {
		
		return _paramList.get(name);
		
	}
	
	public Set<String> getParamNames() {
		
		return _paramList.keySet();
		
	}
	
	public void newParameter(String name, String value) {
		
		_paramList.put(name, value);
		
	}
	
	public void removeParameter(String name) {
		
		_paramList.remove(name);
		
	}
	
	public void removeAllParameters() {
		
		_paramList.clear();
		
	}

}
