#!/usr/bin/env bash

_systheme_completions(){

	local cur prev

	COMPREPLY=()

	if [ $COMP_CWORD -lt 2 ]; then

		COMPREPLY=($(compgen -W "$(ls ~/.config/systheme/systhemes)" "${COMP_WORDS[COMP_CWORD]}"))

	fi

}

complete -F _systheme_completions systheme
