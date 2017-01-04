#!/bin/bash
SCRIPT_LOCATION=$(cd $(dirname $0);echo $PWD)


xcodebuild \
	-workspace ${SCRIPT_LOCATION}/../OpenPGP.xcworkspace \
	-scheme ios_runner -destination 'platform=iOS Simulator,name=iPhone 7,OS=10.1' \
	-sdk iphonesimulator \
	test

#| xcpretty --test --color
