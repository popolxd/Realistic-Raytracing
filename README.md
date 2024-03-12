# Realistic Raytracing

Moje terajšie chápanie physically based raytracingu:
- keď dopadne svetlo na povrch, tak má 2 možnosti. Môže sa odraziť alebo preniknúť do materiálu.
- keď sa odrazí (specular light), tak si väčšinou zachováva pôvodnú farbu svetla (v praxi to znamená že specularColor = (Vector3){1, 1, 1})
- odrazenie môže byť hladké alebo drsné, tento parameter mi kontroluje roughness
- ak prenikne do materiálu, tak materiál pohltí svetlo, ktoré bežne pohlcuje a môžu sa stať 2 veci. Ak je object priesvitný, tak svetlo pokračuje cez neho ďalej pod nejakým iným uhlom (refraction), ak nie, tak tesne pod povrchom sa poodráža na random smery a vyletí z materiálu rovnakou stranou na akýkoľvek smer (diffuse light)
- v oboch prípadoch sa odrazené alebo prepustené svetlo prispôsobí farbe objektu.
- pri oboch týchto svetlách treba nejako zohľadniť, že svetlo dopadané na ten povrch ešte treba nejakým spôsobom upraviť, podľa toho, ako je natočené svetlo (Lamberts cosine law, v praxi trochu biasnem direction odrazu k normalu)
- pri specular reflection toto riešiť nie je treba

Features:
- spheres, planes, disks, triangles
- difusse light
- specular light
- sky light
- transparency (transmission)
- refraction
- depth of field
- some simple post-processing (not here, too inefficent to be real time)
- image saving system (basic)

Missing pieces:
- fancier methods (maybe in the future, for example Fresnel reflection)
- multithreading
- general optimization
- post processing