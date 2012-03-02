/**
 * 
 */
package mapeditor;

import mapeditor.controler.System;
import mapeditor.view.MainWindow;

/**
 * @author Guibrush
 *
 */
public class MapEditor {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		System system = new System();
		
		MainWindow window = new MainWindow(system);
		
		window.show();

	}

}
