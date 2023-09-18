#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "imgui/imgui.h"
#include "imbase/window.hpp"
#include "imbase/texture.hpp"
#include "imbase/launcher.hpp"

int main(void) {
	ImBase::Window::Init(600, 480, "Lmao Ass");
	ImBase::Window::SetMaxFPS(50);

	#define GenValInRange(min, max) (rand() % (max + 1 - min) + min)
	constexpr int TexWidth = 128;
	constexpr int TexHeight = 128;
	float TexScale = 2.5f;

	unsigned char pixels[TexWidth * TexHeight * 4] = { 255 };
	memset(&pixels, 255, TexWidth * TexHeight * 4);

	ImBase::Texture Tex(TexWidth, TexHeight, pixels);

	srand(time(NULL));
	while (!ImBase::Window::ShouldClose()) {
		ImBase::Window::NewFrame();
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Links")) {
				if (ImGui::MenuItem("GitHub")) {
					ImBase::Launcher::OpenUrl("https://github.com/csprite");
				}
				if (ImGui::MenuItem("Website")) {
					ImBase::Launcher::OpenUrl("https://csprite.github.io");
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::ShowMetricsWindow();

		for (int y = 0; y < TexHeight; y++) {
			for (int x = 0; x < TexWidth; x++) {
				*(&pixels[(((y * TexWidth) + x) * 4)] + 0) = GenValInRange(0, 255);
				*(&pixels[(((y * TexWidth) + x) * 4)] + 1) = GenValInRange(0, 255);
				*(&pixels[(((y * TexWidth) + x) * 4)] + 2) = GenValInRange(0, 255);
			}
		}
		Tex.Update(pixels);
		if (ImGui::Begin("Changing Texture", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Image(reinterpret_cast<ImTextureID>(Tex.id), { TexWidth * TexScale, TexHeight * TexScale });
			ImGui::SliderFloat("Scale", &TexScale, 2.0f, 4.0f);
			ImGui::End();
		}

		ImBase::Window::EndFrame();
	}

	ImBase::Window::Destroy();
	return 0;
}

