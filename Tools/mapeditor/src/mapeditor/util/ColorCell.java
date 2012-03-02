/**
 * 
 */
package mapeditor.util;

import java.awt.Color;
import java.util.HashMap;
import java.util.Set;

/**
 * @author Guibrush
 *
 */
public class ColorCell extends ColorElement {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private HashMap<String, String> _paramList;
	
	public ColorCell(Color color, CellType type) {
		
		super(color, type);
		
		_paramList = new HashMap<String, String>();
		
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
	
	public String getParameter(String name) {
		
		return _paramList.get(name);
		
	}
	
	public Set<String> getParamNames() {
		
		return _paramList.keySet();
		
	}
	
	public boolean equals(Object obj) {
		
		if (obj == null)
			return false;
		else
			if (obj instanceof ColorCell) {
				if (((ColorCell) obj).getType().equals(super.getType()))
					return true;
				else
					return false;
			}
			else
				return false;
		
	}

}
