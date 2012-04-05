/**
 * 
 */
package mapeditor.controler;

import java.io.*;
import java.util.TreeSet;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.awt.image.*;
import javax.imageio.*;
import javax.swing.*;

import mapeditor.model.*;
import mapeditor.util.*;

/**
 * @author Danny
 *
 */
public class HeightMapExporter {
	
	BufferedImage _hmImage;
	int _imageWidth, _imageHeight;
	Map _currentMap;
	Preferences _preferences;

	public HeightMapExporter(int width, int height, Preferences currentPref)
	{
		_imageWidth = width * 16;
		_imageHeight = height * 16;
		_preferences = currentPref;
		
		_hmImage = new BufferedImage(_imageWidth, _imageHeight, BufferedImage.TYPE_BYTE_GRAY);
	}
	
	private Position getMapPosition(int x, int y)
	{
		int relX = x * _currentMap.getMapWidth() / _imageWidth;
		int relY = y * _currentMap.getMapHeight() / _imageHeight;
		
		return new Position(relX, relY);
	}
	
	public void ProcessMap (Map currentMap)
	{
		_currentMap = currentMap;
		
		for (int y = 0; y < _imageHeight; y++)
			for (int x = 0; x < _imageWidth; x++)
			{
				String paramValue = _preferences.getCellParameter(
						_currentMap.getCell(getMapPosition(x,y)).getType(),
						"height");
				byte hbyte = (byte) Integer.parseInt(paramValue);
				_hmImage.setRGB(x, y, hbyte);
			}
	}
	
	public void SaveImageHeightmap (File saveFile)
	{        
        try {
            ImageIO.write(_hmImage, "png", saveFile);
            
        } catch (IOException ex) {
        	
        }
	}

}
