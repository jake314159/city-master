
# Where the temp image files are stored
mkdir images/temp



python sprite_line_maker.py images/temp/1_ground.png v images/1_ground/*.png
python sprite_line_maker.py images/temp/2_highlight.png v images/2_highlight/*.png
python sprite_line_maker.py images/temp/3_single_tile_buildings.png v images/3_single_tile_buildings/*.png

python sprite_line_maker.py images/tile_sheet.png h images/temp/*.png

rm -rdf images/temp
