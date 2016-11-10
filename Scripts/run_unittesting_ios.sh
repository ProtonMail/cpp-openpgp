#!/bin/bash

xcodebuild \
	-workspace ${PWD}/../OpenPGP.xcworkspace \
	-scheme ios_runner -destination 'platform=iOS Simulator,name=iPhone 7,OS=10.1' \
	-sdk iphonesimulator \
	test

#| xcpretty --test --color
