#include "UIContext.h"
#include <functional>

#include "Engine.h"

UIContext* UIContext::instance = 0;

UIContext::UIContext() {

	shader = new Shader("resources/shader/vertex2.glsl", "resources/shader/frag2.glsl");
	dockspace = new DockSpace();
	//overlayElement = new LayoutOverlay(width,height);
	float ndc[] = { 
		1.0, 1.0 ,
		1.0,-1.0, 
		-1.0,1.0, 
		-1.0,-1.0, 
		1.0,-1.0, 
		-1.0,1.0,
	};
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &instancevbo);
	glBindBuffer(GL_ARRAY_BUFFER, instancevbo);
	glBufferData(GL_ARRAY_BUFFER, MAX_COMPONENTS * sizeof(Element), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ndc), ndc, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, instancevbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, color)));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, size)));
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);

	glVertexAttribIPointer(4, 1, GL_INT, sizeof(Element), (void*)(offsetof(Element, id)));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);

	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, clipRect)));
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(5, 1);

	
	
	
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void UIContext::init(int width, int height, Engine* engine)
{
	this->engine = engine;
	rendersystem = SystemCoordinator::getInstance()->RegisterSystem<RenderSystem>();
	scrollrendersystem = SystemCoordinator::getInstance()->RegisterSystem<ScrollbarRenderSystem>();
	treenoderenderer = SystemCoordinator::getInstance()->RegisterSystem<TreeNodeRenderSystem>();
	scrollsystem = SystemCoordinator::getInstance()->RegisterSystem<ScrollableSystem>();
	updatesystem = SystemCoordinator::getInstance()->RegisterSystem<UpdateSystem>();
	clicksystem = SystemCoordinator::getInstance()->RegisterSystem<ClickSystem>();
	iconrenderer = SystemCoordinator::getInstance()->RegisterSystem<IconRenderSystem>();
	int w = Engine::getScreenWidth(), h = Engine::getScreenHeight();
	rendersystem->Initialize(w,h);
	scrollrendersystem->Initialize(w,h);
	treenoderenderer->Initialize(w,h);
	scrollsystem->Initialize();
	updatesystem->Initialize();
	clicksystem->Initialize();
	iconrenderer->Initialize(w,h);
	testobject = new ECSAssetBrowser(glm::vec2(0,0), glm::vec2(300,Engine::getScreenHeight()), engine->getApplication());
	setSize(width,height);
}

void UIContext::add(UIComponent* component) {
	component->getUIElements(dataBuffer, instanceData);

	rootComponents.reserve(rootComponents.size() + 1);
	rootComponents.emplace_back(component);
}



void UIContext::setup() {
	int n = 0, m = 0;
	size_t size = 0;
	//instanceData.reserve(instanceData.size() + dataBuffer.size());
	glBindBuffer(GL_ARRAY_BUFFER, instancevbo);
	for (int i = 0; i < dataBuffer.size(); i++) {
		//rootComponents[i]->DrawComponent();
		
		
		
		//instanceData.emplace_back(&dataBuffer[i]);
		
		
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Element) * dataBuffer.size(), dataBuffer.data());
	//std::vector<Element> fw(dataBuffer.size());
	//glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Element) * dataBuffer.size(), fw.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//overlayElement->end();
	//eventHandler->registerEvent(new Event<const glm::vec2&>("drag", std::function<void(const glm::vec2&)>(std::bind(&UIContext::onClick,this,std::placeholders::_1))));
}

void UIContext::setSize(int& width, int& height) {
	int a = this->width - width, b = this->height - height;
	this->width = width, this->height = height;
	shader->use();
	glUniform1f(glGetUniformLocation(shader->getId(), "width"), width);
	glUniform1f(glGetUniformLocation(shader->getId(), "height"), height);
	for (auto& p : rootComponents) {
		//p->size.x += a;
		//p->size.y += b;
		//p->Update();
	}
}

void UIContext::DrawComponents(Engine& engine) {
	
	//float aspect = (float)width / height;
	
	/*int i = 0;
	glBindBuffer(GL_ARRAY_BUFFER, instancevbo);
	for (auto& p : rootComponents) {
		
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(UIElements) * p->uielements.size(), p->uielements.data());
		
		
		for (auto& k : p->DrawComponent()) {
			instanceData[i] = k;
			i++;
		}
		i++;
	}*/
	for (auto& p : rootComponents) {
		p->UpdateElement();
	}
	shader->use();
	glm::mat4 mat = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(mat));
	glBindVertexArray(vao);
	
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, instanceData.size());

	for (auto& p : rootComponents)
	{
		p->render(engine);
	}

	//overlayElement->render();
	if (state == DRAG)
	{
		//dockspace->end();
		//dockspace->render();
	}
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << err << " uicontext" << std::endl;
	}

	scrollsystem->Update();
	clicksystem->Update();
	updatesystem->Update();
	rendersystem->Update();
	scrollrendersystem->Update();

	//systems that draw child components
	glEnable(GL_SCISSOR_TEST);
	treenoderenderer->Update(testobject->getId());
	iconrenderer->Update();
	glDisable(GL_SCISSOR_TEST);


	glBindVertexArray(0);
}

int UIContext::findComponent(glm::vec2 pos) {
	int id = -1;
	for (auto& p : instanceData) {
		if (pos.x >= p->position.x && pos.x <= p->position.x + p->size.x && pos.y >= p->position.y && pos.y <= p->position.y + p->size.y) {
			id = p->getComponentId();
		}
	}
	//return id == targetId ? -2 : id;
	return id;
}

void UIContext::pack() {
}

void UIContext::onClick(glm::vec2 pos) {
	int id,cid,rootid=0;
	id = findComponent(pos);
	if(id != -2) targetId = id;
	if ((id) >= 0) {
		
		std::cout << instanceData[targetId]->size.x << std::endl;
		cid = instanceData[targetId]->onClick(pos);
		if (cid == -1) return;
		std::cout << cid << " cid" << std::endl;
		for (auto& p : rootComponents) {
			if (cid >= p->getComponentId()) rootid = p->getComponentId();
		}
		//onUpdate(rootid,cid);
		updateBatches.push_back({rootid,cid});
		//queueEvent("update", rootid, cid);
	}
	
}

void UIContext::onDrag(glm::vec2 pos, glm::vec2 pos2) {
	//std::cout << "drag" << std::endl;
	if (targetId == -1) {
		return;
	}
	int cid = 0, rootid = 0;
	cid = instanceData[targetId]->onDrag(pos,pos2);
	if (cid == -1 || !instanceData[targetId]->Draggable()) return;
	state = DRAG;
	shader->use();
	glUniform1i(glGetUniformLocation(shader->getId(), "state"), 1);
	for (auto& p : rootComponents) {
		if (cid >= p->getComponentId()) rootid = p->getComponentId();
	}
	//queueEvent("update", rootid, cid);
	//callEvent("update", rootid, cid);
	//onUpdate(rootid,cid);
	updateBatches.push_back({rootid,cid});
}

void UIContext::onRelease(glm::vec2 pos) {
	std::cout << "release" << std::endl;
	if (state == 2) {
		shader->use();
		glUniform1i(glGetUniformLocation(shader->getId(), "state"), 0);
	}
}

void UIContext::onDoubleClick(glm::vec2 pos) {
	std::cout << "double click" << std::endl;
	int id = findComponent(pos);
	if (id != -2 && id != -1) onClick(pos);
	else if (id == -2)
	{
		int cid = 0, rootid = 0;
		cid = instanceData[targetId]->onDoubleClick(pos);
		if (cid == -1) return;
		for (auto& p : rootComponents) {
			if (cid >= p->getComponentId()) rootid = p->getComponentId();
		}
		//queueEvent("update", rootid, cid);
		updateBatches.push_back({rootid,cid});
		//onUpdate(rootid,cid);
	}
}

void UIContext::onUpdate(int start, int end) {
	//std::cout << start << ' ' << end << std::endl;
	for (int i = start; i <= end; i++) dataBuffer[i] = instanceData[i]->uielement;
	std::vector<Element> v(dataBuffer.begin()+start,dataBuffer.begin()+end+1);
	glBindBuffer(GL_ARRAY_BUFFER, instancevbo);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Element) * start, sizeof(Element) * (end+1), v.data());
	//glBufferSubData(GL_ARRAY_BUFFER, 0, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void UIContext::update()
{
	for (auto& p : updateBatches)
	{
		onUpdate(p.start,p.end);
	}

	updateBatches.clear();
}
