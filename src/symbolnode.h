//
// Created by smigii on 2021-09-02.
//

#ifndef SYSTHEME_SYMBOLNODE_H
#define SYSTHEME_SYMBOLNODE_H

#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace systheme {

	class SymbolNode {

	public:

		virtual void write_symbol(std::ofstream& ofs) const = 0;
		[[nodiscard]] virtual std::string get_data() const = 0;

	};

	// ----------------------------------------------------------
	// ----------------------------------------------------------
	// ----------------------------------------------------------

	class SymbolStringNode: public SymbolNode {

	private:
		const std::string data;

	public:
		SymbolStringNode();
		explicit SymbolStringNode(std::string data);
		SymbolStringNode(const SymbolStringNode& other);
		SymbolStringNode(SymbolStringNode&& other) noexcept ;

		void write_symbol(std::ofstream& ofs) const override;
		[[nodiscard]] std::string get_data() const override;

	};

	// ----------------------------------------------------------
	// ----------------------------------------------------------
	// ----------------------------------------------------------

	class SymbolFileNode: public SymbolNode {

	private:
		const fs::path path;

	public:
		SymbolFileNode();
		explicit SymbolFileNode(fs::path path);
		SymbolFileNode(const SymbolFileNode& other);
		SymbolFileNode(SymbolFileNode&& other) noexcept;

		void write_symbol(std::ofstream& ofs) const override;
		[[nodiscard]] std::string get_data() const override;

	};
}


#endif //SYSTHEME_SYMBOLNODE_H
