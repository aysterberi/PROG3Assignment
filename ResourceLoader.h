#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <SDL_hints.h>
#include <map>

class ResourceLoader
{
public:
	
	/*
	 * Represents the type of a specific
	 * bundle. E.g. audio, graphics, text. 
	 */
	enum BundleType {audio, graphics, text};
	/*
	* ResourceBundles represent an abstract
	* package of disk-locations for resources
	* and a specific key with which to refer to these
	* resources once loaded by the engine.
	*
	* Each bundle contains a unique bundle
	* identifier, a type, and a dict for the vals.
	* K = item_identifier, V = disk location path
	* The type shall be verified by the various load functions 
	* and a mismatch between declared bundle type
	* and the type of load method shall cause a loading failure.
	*/
	struct ResourceBundle
	{
		Uint64 UUID;
		BundleType type;
		std::map<std::string, std::string> resources;

	};
	ResourceLoader();
	~ResourceLoader();
	void LoadAudioBundle(ResourceBundle bundle); //TODO: skapa en vettig bundle
	void LoadGraphicsBundle(ResourceBundle bundle);
	void LoadTextBundle(ResourceBundle bundle);
};

#endif
